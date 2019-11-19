#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXQUEUES 3

int CTR = 0;
int HEAD = 0;
int TAIL = 0;
struct MTQ *registry;

struct mealTicket {
	int ticketNum;
	char *dish;
};

struct MTQ {
	char *name;
	struct mealTicket **buffer;
	int head;
	int tail;
	int length;
};

int enqueue(char *MTQ_ID, struct mealTicket *MT) {
	int idx;
	for (int i=0; i<=MAXQUEUES; i++) {
		if (strcmp(MTQ_ID, registry[i].name) == 0) {
			idx = i;
		}
	}
	
	if (registry[idx].length >= 3) { /* queue full */
		//printf("Queue is full. Unable to push element: %s\n", MT->dish);
		return 0;
	}
	else { /* queue not full */
		registry[idx].buffer[registry[idx].head] = MT;
		if (registry[idx].head == 2) {
			registry[idx].head = 0;
		}
		else {
			registry[idx].head++;
		}
		registry[idx].length++;
	}
	return 1;
}

//int dequeue(char *MTQ_ID, int ticketNum, struct mealTicket *MT) {
int dequeue(char *MTQ_ID, int ticketNum, struct mealTicket *MT) {
	int idx;
	for (int i=0; i<=MAXQUEUES; i++) {
		if (strcmp(MTQ_ID, registry[i].name) == 0) {
			idx = i;
		}
	}

	if (registry[idx].length == 0) { /* queue empty */
		//printf("Queue is empty. Unable to pop element.\n");
		return 0;
	}
	else { /* queue not empty */
		int check = 0;
		for (int i=0; i<3; i++) {
			int num = registry[idx].buffer[registry[idx].tail]->ticketNum;
			if (num == ticketNum) {
				MT->ticketNum = num;
				MT->dish = registry[idx].buffer[registry[idx].tail]->dish;
				printf("Queue: %s - Ticket Number: %d - Dish: %s\n", registry[idx].name, MT->ticketNum, MT->dish);
				registry[idx].buffer[registry[idx].tail] = NULL;
				if (registry[idx].tail >= 2) {
					registry[idx].tail = 0;
				}
				else {
					registry[idx].tail++;
				}
				registry[idx].length--;
				return 1;
			}
		}	
		MT->ticketNum = registry[idx].buffer[registry[idx].tail]->ticketNum;
		MT->dish = registry[idx].buffer[registry[idx].tail]->dish;
		printf("Queue: %s - Ticket Number: %d - Dish: %s\n", registry[idx].name, MT->ticketNum, MT->dish);
		registry[idx].buffer[registry[idx].tail] = NULL;
		if (registry[idx].tail >= 2) {
			registry[idx].tail = 0;
		}
		else {
			registry[idx].tail++;
		}
		registry[idx].length--;
	}
	return 1;
}

int main() {
	struct MTQ Breakfast;
	struct MTQ Lunch;
	struct MTQ Dinner;
	struct MTQ Bar;

	Breakfast.name = "Breakfast";
	Lunch.name = "Lunch";
	Dinner.name = "Dinner";
	Bar.name = "Bar";

	Breakfast.buffer = malloc(3 * sizeof(struct mealTicket*));
	Lunch.buffer = malloc(3 * sizeof(struct mealTicket*));
	Dinner.buffer = malloc(3 * sizeof(struct mealTicket*));
	Bar.buffer = malloc(3 * sizeof(struct mealTicket*));

	for (int i=0; i<3; i++) {
		Breakfast.buffer[i] = NULL;
		Lunch.buffer[i] = NULL;
		Dinner.buffer[i] = NULL;
		Bar.buffer[i] = NULL;
	}

	registry = malloc(4 * sizeof(struct MTQ));
	registry[0] = Breakfast;
	registry[1] = Lunch;
	registry[2] = Dinner;
	registry[3] = Bar;

	for (int i=0; i<4; i++) {
		registry[i].head = 0;
		registry[i].tail = 0;
		registry[i].length = 0;
	}

	/* Test case A: Dequeue when a queue is empty */
	struct mealTicket MT;
	char *result;
	if (dequeue("Breakfast", 1, &MT) == 0) {
		result = "Fail";
	}
	else {
		result = "Success";
	}
	printf("Test Case: A - Result: %s\n", result);

	/* Test case D: Enqueue when a queue is empty */
	struct mealTicket testTicket;
	testTicket.ticketNum = 23;
	testTicket.dish = "Pancakes";
	if (enqueue("Breakfast", &testTicket) == 0) {
		result = "Fail";
	}
	else {
		result = "Success";
	}
	printf("Test Case: D - Result: %s\n", result);

	/* Breakfast meal tickets */
	struct mealTicket ticket1;
	ticket1.ticketNum = 1;
	ticket1.dish = "Eggs";

	struct mealTicket ticket2;
	ticket2.ticketNum = 2;
	ticket2.dish = "Cereal";

	struct mealTicket ticket3;
	ticket3.ticketNum = 3;
	ticket3.dish = "Toast";

	enqueue("Breakfast", &ticket1);
	enqueue("Breakfast", &ticket2);
	enqueue("Breakfast", &ticket3);

	/* Lunch meal tickets */
	struct mealTicket ticket4;
	ticket4.ticketNum = 4;
	ticket4.dish = "Sandwich";

	struct mealTicket ticket5;
	ticket5.ticketNum = 5;
	ticket5.dish = "Salad";

	struct mealTicket ticket6;
	ticket6.ticketNum = 6;
	ticket6.dish = "Burrito";

	enqueue("Lunch", &ticket4);
	enqueue("Lunch", &ticket5);
	enqueue("Lunch", &ticket6);

	/* Dinner meal tickets */
	struct mealTicket ticket7;
	ticket7.ticketNum = 7;
	ticket7.dish = "Spaghetti";

	struct mealTicket ticket8;
	ticket8.ticketNum = 8;
	ticket8.dish = "Sushi";

	struct mealTicket ticket9;
	ticket9.ticketNum = 9;
	ticket9.dish = "Salmon";

	enqueue("Dinner", &ticket7);
	enqueue("Dinner", &ticket8);
	enqueue("Dinner", &ticket9);

	/* Bar meal tickets */
	struct mealTicket ticket10;
	ticket10.ticketNum = 10;
	ticket10.dish = "Wine";

	struct mealTicket ticket11;
	ticket11.ticketNum = 11;
	ticket11.dish = "Mojito";

	struct mealTicket ticket12;
	ticket12.ticketNum = 12;
	ticket12.dish = "Margarita";

	enqueue("Bar", &ticket10);
	enqueue("Bar", &ticket11);
	enqueue("Bar", &ticket12);

	/* Test case C: Enqueue when a queue is full */
	if (enqueue("Dinner", &MT) == 0) {
		result = "Fail";
	}
	else {
		result = "Success";
	}
	printf("Test Case: C - Result: %s\n", result);

	/* Test case B: Dequeue when a queue is full */
	if (dequeue("Breakfast", 1, &MT) == 0) {
		result = "Fail";
	}
	else {
		result = "Success";
	}
	printf("Test Case: B - Result: %s\n", result);

	/* In a round robin fashion pop a meal ticket from each
	   queue and display it until all queues are empty. */
	for (int i=0; i<=3; i++) {
		for (int j=0; j<=2; j++) {
			dequeue(registry[i].name, 1, &MT);
		}
	}

	free(Breakfast.buffer);
	free(Lunch.buffer);
	free(Dinner.buffer);
	free(Bar.buffer);
	free(registry);
}