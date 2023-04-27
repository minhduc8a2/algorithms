#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {
	char name[20];
	float weight;
	float value;
	float valuePerWeight;
} Thing;

Thing *  initThingList(int *n, float *w) {

	
	scanf("%d%f", n, w);

	Thing* thingList = (int*)malloc((*n) * sizeof(Thing));
	int i;
	for ( i = 0; i < *n; i++)
	{
		scanf("%f%f%[^\n]", &thingList[i].weight, &thingList[i].value, thingList[i].name);
		thingList[i].valuePerWeight = thingList[i].value / thingList[i].weight;
	}
	return thingList;

}
void printThings(Thing* thingList, int numberOfThings) {
	int i;
	for (i = 0; i < numberOfThings; i++)
	{
		printf("weight: %f, value: %f, name: %s\n", thingList[i].weight, thingList[i].value, thingList[i].name);
	}
}


void copyThingToThing(Thing* a, Thing* b) {
	strcpy(a->name, b->name);
	a->weight = b->weight;
	a->value = b->value;
	a->valuePerWeight = b->valuePerWeight;

}
void swapThing(Thing* a, Thing* b) {
	Thing temp;
	copyThingToThing(&temp, a);
	copyThingToThing(a, b);
	copyThingToThing(b, &temp);

}

void bubbleSort(Thing* thingList, int numberOfThings) {
	int i,k;
	for ( i = 0; i < numberOfThings; i++)
	{
		for ( k = 0; k < numberOfThings-1; k++)
		{
			if (thingList[k].valuePerWeight < thingList[k+1].valuePerWeight) {
				swapThing(&thingList[k], &thingList[k + 1]);
			}
		}
	}
}



void KnapsackBranchAndBound(Thing * thingList,int thingIndex, float totalValue, float remainWeight, float upperBound, float *temporaryBestValue, int numberOfThings) {

	if (upperBound < *temporaryBestValue) return;
	int i;
	int canContinue = 0;
	for (i = 0;i < numberOfThings;i++) {
		if (remainWeight / thingList[i].weight > 1) {
			canContinue = 1;
			break;
		}
	}
	if (!canContinue) {
		if (totalValue > *temporaryBestValue) *temporaryBestValue = totalValue;
		return;
	}
	int maxNumberOfThing = (int)(remainWeight / thingList[thingIndex].weight);
	 i = maxNumberOfThing;
	for (;i >=0 ;i--) {
		int nextThingIndex = thingIndex + 1;
		float nextTotalValue = totalValue + i * thingList[thingIndex].value;
		float nextRemainWeight = remainWeight - i * thingList[thingIndex].weight;
		float nextUpperBound = nextTotalValue + nextRemainWeight * thingList[nextThingIndex].valuePerWeight;
		KnapsackBranchAndBound(thingList, nextThingIndex, nextTotalValue, nextRemainWeight, nextUpperBound, temporaryBestValue,numberOfThings);
	}

}
int main() {
	int i;
	float bagCapability;
	int numberOfThings;
	float bestValue = -1;
	freopen("dothi.txt", "r", stdin);
	Thing * thingList = initThingList(&numberOfThings,&bagCapability);
	//printThings(thingList, numberOfThings);
	bubbleSort(thingList, numberOfThings);
	printThings(thingList, numberOfThings);
	KnapsackBranchAndBound(thingList, 0, 0, bagCapability, thingList[0].valuePerWeight * bagCapability, &bestValue, numberOfThings);
	printf("%f", bestValue);
	return 0;
}
