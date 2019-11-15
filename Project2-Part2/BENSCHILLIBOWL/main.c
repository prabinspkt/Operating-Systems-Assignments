#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "BENSCHILLIBOWL.h"

// Feel free to play with these numbers! This is a great way to
// test your implementation.
#define BENSCHILLIBOWL_SIZE 100
#define NUM_CUSTOMERS 10
#define NUM_COOKS 5
#define ORDERS_PER_CUSTOMER 5
#define EXPECTED_NUM_ORDERS NUM_CUSTOMERS * ORDERS_PER_CUSTOMER

// Global variable for the restaurant.
BENSCHILLIBOWL *bcb;

/**
 * Thread funtion that represents a customer. A customer should:
 *  - allocate space (memory) for an order.
 *  - select a menu item.
 *  - populate the order with their menu item and their customer ID.
 *  - add their order to the restaurant.
 */
void* BENSCHILLIBOWLCustomer(void* tid) {
    int customer_id = (int)(long) tid;
	
		// Create order and add it to the queue
    for (int i = 0; i < ORDERS_PER_CUSTOMER; i++) {
      Order * cust_order = (Order*) malloc(sizeof(Order));
      cust_order->menu_item = PickRandomMenuItem();
      cust_order->customer_id = customer_id;
      // Need to set this to NULL when customer order is made
      cust_order->next = NULL;
      int order_num = AddOrder(bcb, cust_order);
      printf("Order %d created for customer %d\n", order_num, customer_id);
    }
	return NULL;
}

/**
 * Thread function that represents a cook in the restaurant. A cook should:
 *  - get an order from the restaurant.
 *  - if the order is valid, it should fulfill the order, and then
 *    free the space taken by the order.
 * The cook should take orders from the restaurants until it does not
 * receive an order.
 */
void* BENSCHILLIBOWLCook(void* tid) {
  int cook_id = (int)(long) tid;
	int orders_fulfilled = 0;
  
	// Get the first order in the queue to be fulfilled
  Order *cook_order;
	cook_order = GetOrder(bcb);
  while((cook_order != NULL)) {
		printf("Cook #%d fulfilled %d orders\n", cook_id, orders_fulfilled);
    free(cook_order);
    orders_fulfilled++;
		// Get another order from the queue
		cook_order = GetOrder(bcb);
  }
	return NULL;
}

/**
 * Runs when the program begins executing. This program should:
 *  - open the restaurant
 *  - create customers and cooks
 *  - wait for all customers and cooks to be done
 *  - close the restaurant.
 */
int main() {
    bcb = OpenRestaurant(BENSCHILLIBOWL_SIZE, EXPECTED_NUM_ORDERS);
    
    // Declare arrays for customer and cook threads and their ids
    pthread_t customers[NUM_CUSTOMERS];
    int customer_ids[NUM_CUSTOMERS];
		pthread_t cooks[NUM_COOKS];
    int cook_ids[NUM_COOKS];
    
    // Create threads for both customer and cook functions
    for (int j = 0; j < NUM_CUSTOMERS; j++) {
      customer_ids[j] = j+1;
      pthread_create(&(customers[j]), NULL, BENSCHILLIBOWLCustomer, &(customer_ids[j]));
    }
    for (int k = 0; k < NUM_COOKS; k++ ) {
      cook_ids[k] = k+1;
      pthread_create(&(cooks[k]), NULL, BENSCHILLIBOWLCook, &(cook_ids[k]));
    }
  
    // Wait for all customer and cook processes to be done
    for (int a = 0; a < NUM_CUSTOMERS; a++) {
      pthread_join(customers[a], NULL);
    }
    for (int b = 0; b < NUM_COOKS; b++) {
      pthread_join(cooks[b], NULL);
    }
  
    // Finally, close the restaurant when all the customer and cook processes have been completed
    CloseRestaurant(bcb);
  
    return 0;
}