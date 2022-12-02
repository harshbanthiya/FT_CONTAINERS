# REDBLACK tree

- Self Balanced binary trees which stay balanced after insertion or deletion <br>

## ft::_red_black_tree<Key, Value>
- Key must be of a type which is comparable with < > == !=

## Debug 
- setting red_black_debug to 1 turns it on, 0 turns it off 

## Types 

### value_ptr is a pointer to the data, ft::pair<key, value>
- value_ptr->first == KEY
- value_ptr->second == VALUE
- the key is supposed to be READ_ONLY 

# Public Member Functions 

## bool empty() - returns true if empty, false otherwise

## size_type  *size() - returns size of tree, usually size_type is size_t 

## void clear() - deletes and frees all the data 

## bool find(Key k) - returns true if key already is tree false if not 

## value_ptr get_value(Key k) - returns null if not found and value_ptr to data if found

## void set_value(Key k, Value v) - changes value of key if k found, insert new Key with value if key not found 

## void erase(value_ptr data) - if key found, delete element from tree 

## void erase(Key k) - overload with just Key 

## void insert(Key k, Value v) - inserts new element in tree ; does nothing if key already exists <br>

## void print() -- print the whole tree
## testing - test_rb.cpp g++ test_rb.cpp -o test


 


