#include <stdio.h>
#include <string.h>
#define MAXQUEUES 4

int CTR = 0;
int HEAD = 0;
int TAIL = 0;
struct MTQ *registry[MAXQUEUES];

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
	for (int i=0; i<MAXQUEUES; i++) {
		if (strcmp(MTQ_ID, registry[i]->name) == 0) {
			idx = i;
		}
	}
	if (registry[idx]->length >= 3) { /* queue full */
		printf("Queue is full. Unable to push element: %s\n", MT->dish);
		return 0;
	}
	else { /* queue not full */
		registry[idx]->buffer[registry[idx]->head] = MT;
		if (registry[idx]->head == 2) {
			registry[idx]->head = 0;
		}
		else {
			registry[idx]->head++;
		}
		registry[idx]->length++;
	}
	return 1;
}

int dequeue(char *MTQ_ID, int ticketNum, struct mealTicket *MT) {
	int idx;
	for (int i=0; i<MAXQUEUES; i++) {
		if (strcmp(MTQ_ID, registry[i]->name) == 0) {
			idx = i;
		}
	}
	if (registry[idx]->length == 0) { /* queue empty */
		printf("Queue is empty. Unable to pop element.\n");
		return 0;
	}
	else { /* queue not empty */
		//struct mealTicket **tmp = registry[idx]->buffer[registry[idx]->tail];
		MT->ticketNum = registry[idx]->buffer[registry[idx]->tail]->ticketNum;
		MT->dish = registry[idx]->buffer[registry[idx]->tail]->dish;
		registry[idx]->buffer[registry[idx]->tail] = NULL;
		printf("Queue: %s - Ticket Number: %d - Dish: %s\n", registry[idx]->name, MT->ticketNum, MT->dish);
		if (registry[idx]->tail == 2) {
			registry[idx]->tail = 0;
		}
		else {
			registry[idx]->tail++;
		}
		registry[idx]->length--;
	}
	return 1;
}

int main() {
	struct MTQ *Breakfast;
	struct MTQ *Lunch;
	struct MTQ *Dinner;
	struct MTQ *Bar;

	Breakfast->name = "Breakfast";
	Lunch->name = "Lunch";
	Dinner->name = "Dinner";
	Bar->name = "Bar";

	for (int i=0; i<3; i++) {
		Breakfast->buffer[i] = NULL;
		Lunch->buffer[i] = NULL;
		Dinner->buffer[i] = NULL;
		Bar->buffer[i] = NULL;
	}

	registry[0] = Breakfast;
	registry[1] = Lunch;
	registry[2] = Dinner;
	registry[3] = Bar;

	for (int i=0; i<4; i++) {
		registry[i]->head = 0;
		registry[i]->tail = 0;
		registry[i]->length = 0;
	}
 
	/* Breakfast meal tickets */
	struct mealTicket *ticket1;
	ticket1->ticketNum = 1;
	ticket1->dish = "Eggs";

	struct mealTicket *ticket2;
	ticket1->ticketNum = 2;
	ticket1->dish = "Cereal";

	struct mealTicket *ticket3;
	ticket1->ticketNum = 3;
	ticket1->dish = "Toast";

	enqueue("Breakfast", ticket1);
	enqueue("Breakfast", ticket2);
	enqueue("Breakfast", ticket3);

	for (int i=0; i<=2; i++) {
		printf("item: %s\n", registry[0]->buffer[i]->dish);
	}

	/* Lunch meal tickets */
/*	struct mealTicket *ticket4;
	ticket1->ticketNum = 4;
	ticket1->dish = "Sandwich";

	struct mealTicket *ticket5;
	ticket1->ticketNum = 5;
	ticket1->dish = "Salad";

	struct mealTicket *ticket6;
	ticket1->ticketNum = 6;
	ticket1->dish = "Burrito";

	enqueue("Lunch", ticket4);
	enqueue("Lunch", ticket5);
	enqueue("Lunch", ticket6);
*/
	/* Dinner meal tickets */
/*	struct mealTicket *ticket7;
	ticket1->ticketNum = 7;
	ticket1->dish = "Spaghetti";

	struct mealTicket *ticket8;
	ticket1->ticketNum = 8;
	ticket1->dish = "Sushi";

	struct mealTicket *ticket9;
	ticket1->ticketNum = 9;
	ticket1->dish = "Salmon";

	enqueue("Dinner", ticket7);
	enqueue("Dinner", ticket8);
	enqueue("Dinner", ticket9);
*/
	/* Bar meal tickets */
/*	struct mealTicket *ticket10;
	ticket1->ticketNum = 10;
	ticket1->dish = "Wine";

	struct mealTicket *ticket11;
	ticket1->ticketNum = 11;
	ticket1->dish = "Mojito";

	struct mealTicket *ticket12;
	ticket1->ticketNum = 12;
	ticket1->dish = "Margarita";

	enqueue("Bar", ticket10);
	enqueue("Bar", ticket11);
	enqueue("Bar", ticket12);
*/
}