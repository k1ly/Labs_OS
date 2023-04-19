#include "pch.h"
#include "OS14_HTAPI.h"

HTHANDLE::HTHANDLE()
{
	this->Capacity = 0;
	this->Size = 0;
	this->SecSnapshotInterval = 0;
	this->MaxKeyLength = 0;
	this->MaxPayloadLength = 0;
}

HTHANDLE::HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512])
{
	this->Capacity = Capacity;
	this->Size = 0;
	this->SecSnapshotInterval = SecSnapshotInterval;
	this->MaxKeyLength = MaxKeyLength;
	this->MaxPayloadLength = MaxPayloadLength;
	strcpy_s(this->FileName, FileName);
}

Element::Element()
{
	this->keylength = 0;
	this->payloadlength = 0;
}

Element::Element(const void* key, int keylength)
{
	this->key = key;
	this->keylength = keylength;
	this->payloadlength = 0;
}

Element::Element(const void* key, int keylength, const void* payload, int payloadlength)
{
	this->key = key;
	this->keylength = keylength;
	this->payload = payload;
	this->payloadlength = payloadlength;
}

Element::Element(Element* oldelement, const void* newpayload, int newpayloadlength)
{
	this->key = oldelement->key;
	this->keylength = oldelement->keylength;
	this->payload = newpayload;
	this->payloadlength = newpayloadlength;
}