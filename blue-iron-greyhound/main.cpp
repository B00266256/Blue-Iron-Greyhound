/*=============================================================================
* Project: Blue Iron Greyhound
* 
=============================================================================*/

#include "TestComponent.h"
#include "InteractiveTestComponent.h"

int main(int argc, char *argv[])
{
	GameObject *testObj = new GameObject("testObj");
	TestComponent *testComponentA = new TestComponent("testComponentA");
	InteractiveTestComponent *testComponentB = new InteractiveTestComponent("testComponentB");

	testObj->addComponent(testComponentA);
	testObj->addComponent(testComponentB);
	
	testObj->init();
	testObj->update();
	testObj->getComponent<InteractiveTestComponent>()->update();
	testObj->update();

	int i = 1;
	do {} while (i != 0);

	return 0;
}