template <class T>
Vec<List<T>*> balanced_copy(Vec<List<T>*> v, size_t k) {
    Vec<List<T>*> res;
    res.data = nullptr;
    res.s = 0;
    res.cap = 0;

    if (k == 0) {
        return res;
    }

    size_t total_nodes = 0;
    for (size_t i = 0; i < v.s; i++) {
        List<T>* curr = v.data[i];
        while (curr != nullptr) {
            total_nodes++;
            curr = curr->next;
        }
    }
    
    if (total_nodes == 0) {
        return res;
    }

    size_t num_lists = (total_nodes + k - 1) / k;
    
    List<T>** new_data = new List<T>*[num_lists];
    List<T>** tails = new List<T>*[num_lists];
    
    for (size_t i = 0; i < num_lists; i++) {
        new_data[i] = nullptr;
        tails[i] = nullptr;
    }

    try {
        size_t global_idx = 0;
        for (size_t i = 0; i < v.s; i++) {
            List<T>* curr = v.data[i];
            while (curr != nullptr) {
                size_t list_idx = global_idx / k;
                
                List<T>* new_node = new List<T>;
                new_node->val = curr->val;
                new_node->next = nullptr;
                
                if (new_data[list_idx] == nullptr) {
                    new_data[list_idx] = new_node;
                    tails[list_idx] = new_node;
                } else {
                    tails[list_idx]->next = new_node;
                    tails[list_idx] = new_node;
                }
                
                curr = curr->next;
                global_idx++;
            }
        }
    } catch (...) {
        for (size_t i = 0; i < num_lists; i++) {
            List<T>* head = new_data[i];
            while (head != nullptr) {
                List<T>* next = head->next;
                delete head;
                head = next;
            }
        }
        delete[] new_data;
        delete[] tails;
        throw;
    }

    res.data = new_data;
    res.s = num_lists;
    res.cap = num_lists;
    
    delete[] tails;
    
    return res;
}
