#[derive(Debug, Clone)]
pub struct HashEntry<T> {
    key: String,
    value: T,
    next: Option<Box<HashEntry<T>>>,
}

#[derive(Debug, Clone)]
pub struct HashTable<T> {
    buckets: Vec<Option<Box<HashEntry<T>>>>,
    size: usize,
}

impl<T: Clone> HashTable<T> {
    pub fn new(size: usize) -> Self {
        Self {
            buckets: vec![None; size],
            size,
        }
    }

    fn hash_function(key: &str) -> u64 {
        let mut hash: u64 = 5381;

        for c in key.chars() {
            hash = ((hash << 5).wrapping_add(hash)) + c as u64;
        }

        hash
    }

    pub fn put(&mut self, key: &str, value: T) {
        let index = Self::hash_function(key) % (self.size as u64);
        let current = &mut self.buckets[index as usize];

        let mut entry = current.clone();

        while let Some(ref mut e) = entry {
            if e.key == key {
                e.value = value;
                return;
            }
            entry = e.next.clone();
        }

        let new_entry = Box::new(HashEntry {
            key: key.to_string(),
            value,
            next: current.take(),
        });

        *current = Some(new_entry);
    }

    pub fn get(&self, key: &str) -> Option<&T> {
        let index = Self::hash_function(key) % (self.size as u64);
        let mut current = &self.buckets[index as usize];

        while let Some(ref entry) = current {
            if entry.key == key {
                return Some(&entry.value);
            }
            current = &entry.next;
        }

        None
    }

    pub fn remove(&mut self, key: &str) -> Option<T> {
        let index = Self::hash_function(key) % (self.size as u64);
        let bucket = &mut self.buckets[index as usize];

        if let Some(entry) = bucket {
            if entry.key == key {
                if let Some(mut removed) = bucket.take() {
                    *bucket = removed.next.take();
                    return Some(removed.value);
                }
            }
        }

        let mut current = bucket;
        while let Some(entry) = current {
            if let Some(ref next) = entry.next {
                if next.key == key {
                    if let Some(mut removed) = entry.next.take() {
                        entry.next = removed.next.take();
                        return Some(removed.value);
                    }
                }
            }
            current = &mut entry.next;
        }
        None
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_put_and_get() {
        let mut table = HashTable::new(10);
        table.put("key1", "value1");
        table.put("key2", "value2");

        assert_eq!(table.get("key1"), Some(&"value1"));
        assert_eq!(table.get("key2"), Some(&"value2"));
        assert_eq!(table.get("non_existent"), None);
    }

    #[test]
    fn test_remove_existing_key() {
        let mut table = HashTable::new(10);
        table.put("key1", "value1");
        table.put("key2", "value2");

        let removed_value = table.remove("key1");
        assert_eq!(removed_value, Some("value1"));
        assert_eq!(table.get("key1"), None);
    }

    #[test]
    fn test_remove_non_existent_key() {
        let mut table = HashTable::new(10);
        table.put("key1", "value1");

        let removed_value = table.remove("non_existent");
        assert_eq!(removed_value, None);
    }

    #[test]
    fn test_collision_handling() {
        let mut table = HashTable::new(10);
        table.put("key1", "value1");
        table.put("kye1", "value2");

        assert_eq!(table.get("key1"), Some(&"value1"));
        assert_eq!(table.get("kye1"), Some(&"value2"));
    }

    #[test]
    fn test_remove_with_collision() {
        let mut table = HashTable::new(10);
        table.put("key1", "value1");
        table.put("kye1", "value2");

        let removed_value = table.remove("key1");
        assert_eq!(removed_value, Some("value1"));
        assert_eq!(table.get("key1"), None);
        assert_eq!(table.get("kye1"), Some(&"value2"));
    }
}
