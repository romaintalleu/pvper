#include <priv/hw/CPU.h>
#include <priv/hw/Gpio.h>
#include <priv/hw/Memory.h>
#include <priv/hw/Serial.h>
#include <priv/base.h>

#include <angle/list.hxx>

using namespace pvper::hw;

void printLinkedListOfUInt32(const angle::List<uint32_t>& linkedList)
{
	Serial& line = pvper::hw::Serial::shared();
	line << "linkedList";
	auto it = linkedList.constIterator();
	while (it == true)
	{
		line << " > " << *it;
		++it;
	}
	line << "\n";
}

EXTERNC void kinit(const uint32_t r0, const uint32_t machCode, const uint32_t atags) {
	assert(r0 == 0);

	Serial& line = pvper::hw::Serial::shared();

	line << (machCode == 0x00000C42 ? "Raspberry Pi detected, everything should be OK for model B.\n" : "Unknown platform, good luck to you!\n");

	angle::List<uint32_t> linkedList;
	printLinkedListOfUInt32(linkedList);
	linkedList.pushFront(0);
	printLinkedListOfUInt32(linkedList);
	linkedList.pushFront(1);
	printLinkedListOfUInt32(linkedList);
	linkedList.pushFront(2);
	printLinkedListOfUInt32(linkedList);
	linkedList.pushBack(3);
	printLinkedListOfUInt32(linkedList);
	linkedList.pushBack(4);
	printLinkedListOfUInt32(linkedList);
	linkedList.pushFront(5);
	printLinkedListOfUInt32(linkedList);
	linkedList.pushBack(6);
	printLinkedListOfUInt32(linkedList);

	line << "this should be print a green \"true\": " << Serial::ForeGreen << true << Serial::Reset << "\n";
	line << "this should be print a red \"false\": " << Serial::ForeRed << false << Serial::Reset << "\n";
}