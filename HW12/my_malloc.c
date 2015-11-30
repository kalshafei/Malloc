#include "my_malloc.h"

/* You *MUST* use this macro when calling my_sbrk to allocate the
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048

/* If you want to use debugging printouts, it is HIGHLY recommended
 * to use this macro or something similar. If you produce output from
 * your code then you may receive a 20 point deduction. You have been
 * warned.
 */
#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x)
#endif


/* our freelist structure - this is where the current freelist of
 * blocks will be maintained. failure to maintain the list inside
 * of this structure will result in no credit, as the grader will
 * expect it to be maintained here.
 * Technically this should be declared static for the same reasons
 * as above, but DO NOT CHANGE the way this structure is declared
 * or it will break the autograder.
 */
metadata_t* freelist;
//INCREASING ORDER
void* my_malloc_size_order(size_t size)
{
	int mysize =  sizeof(metadata_t) + size;
	if (mysize > 2048) {
		ERRNO = SINGLE_REQUEST_TOO_LARGE;
		return NULL;
	}
	metadata_t* temp = freelist;

	int done = 0;
	while(temp != NULL && done != 1) {
		if (temp->in_use == 0 && (temp->size >= mysize)) {
			done = 1;
			if (size + sizeof(metadata_t) * 2 + 1 < temp->size) {
				//Don't Split

			} else {
				//Split and allocate
			}

			// temp->prev->next = temp->next;
			// temp->next->prev = temp->prev;
			// temp-> in_use = 1;
			// temp->next = NULL;
			// temp->prev = NULL;
			temp = remove_node(temp);
		} else {
			temp = temp->next
		}
	}
	if (done == 0) {
		temp = my_sbrk(SBRK_SIZE);
		if (temp == NULL) {
			ERRNO = OUT_OF_MEMORY;
			return NULL
		}
		//SPLIT TEMP UP and add remainder back to freelist in order
		temp->in_use = 1;
		temp->size = size;
		temp->next = NULL;
		temp->prev = NULL;
	}
  	return (char)temp + sizeof(metadata_t); //Check if cast location is correct
}

void* my_malloc_addr_order(size_t size)
{
	int size = sizeof(metadata_t) + size;
  	return NULL;
}

void my_free_size_order(void* ptr)
{
	metadata_t* node = (char*) ptr + sizeof(metadata_t);
	node->in_use = 0;
	node = merge_nodes(node);
	add_node(node, 0);

}

void my_free_addr_order(void* ptr)
{
	add_node(node, 1);
}

// int get_index(size_t size) {
// 	int index = 0;
// 	int mem = 16;
// 	while (mem < size) {
// 		mem = mem * 2;
// 		index++;
// 	}
// 	return index;
// }
metadata_t* merge_nodes(metadata_t* node) {
	metadata_t* right = (char*)node + node->size;
	metadata_t* left = freelist;
	found = 0;
	while(!found) {
		if ((char*)left + left->size == node) {
			found = 1;
		} else {
			left = left->next;	//What if no left is found, or right not found
		}
	}
	if (left->in_use == 0) {
		//merge
	}
	if (right->in_use == 0) {
		//merge
		//Whose pointers do I use
	}
	return node;
}

metadata_t* remove_node(metadata_t* node) {
	metadata_t* next = node->next;
	metadata_t* prev = node->prev;

	int index = get_index(node->size);
	if (prev != NULL && next != NULL) {
		prev->next = next;
		next->prev = prev;
	} else if (prev != NULL && next == NULL) {
		prev->next = NULL;
	} else if (prev == NULL && next != NULL) {
		//metadata_t[index] = NULL;
		next->prev = NULL;
	} else {
		//metadata_t[index] = NULL;
	}
	node->next = NULL;
	node->prev = NULL;
	return node;
}
//If sort = 0, then sort by block size, if sort = 1 then sort by address
void add_node(metadata_t* node, int sort) {
	metadata_t* temp = freelist;
	if (temp == NULL) {	//If first element add to front?

	}
	int done = 0;
	bool result;
	while (done != 1) {
		if (sort == 0) {
			//Compare by block size
			result = temp->size > node->size;
		} else {
			//Compare by Address
			result = temp > node;
		}
		if(result) {
			node->next = temp;
			node->prev = temp->prev;
			temp->prev = node;
			done = 1;
		} else if(temp->next == NULL) {
			node->prev = temp;
			temp->next= node;
			done = 1;
		}
		temp = temp->next;
	}
}
