#include "pch.h"
#include "..\\OS10_HTAPI\\OS10_HTAPI.h"
#pragma comment(lib, "..\\x64\\Debug\\OS10_HTAPI.lib")

TEST(Test_HTAPI, Create_HT) {
	HT::HTHANDLE* ht = nullptr;
	int capacity = 1000;
	int secSnapshotInterval = 5;
	int maxKeyLength = 10;
	int maxPayloadLength = 100;
	LPCSTR filename = "..\\Test_HT.ht";

	ht = HT::Create(capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, filename);

	ASSERT_NE(ht, nullptr);
	EXPECT_EQ(ht->Capacity, capacity);
	EXPECT_EQ(ht->SecSnapshotInterval, secSnapshotInterval);
	EXPECT_EQ(ht->MaxKeyLength, maxKeyLength);
	EXPECT_EQ(ht->MaxPayloadLength, maxPayloadLength);
	char pathname[MAX_PATH];
	GetFullPathNameA(filename, MAX_PATH, pathname, NULL);
	EXPECT_STREQ(ht->FileName, pathname);
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, NotCreate_HT_With_InvalidParameters) {
	HT::HTHANDLE* ht = nullptr;
	int capacity = -1000;
	int secSnapshotInterval = -5;
	int maxKeyLength = -10;
	int maxPayloadLength = -100;

	ht = HT::Create(capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, nullptr);

	ASSERT_EQ(ht, nullptr);
}

TEST(Test_HTAPI, Open_HT) {
	HT::HTHANDLE* ht = nullptr;
	int capacity = 1000;
	int secSnapshotInterval = 5;
	int maxKeyLength = 10;
	int maxPayloadLength = 100;
	LPCSTR filename = "..\\Test_HT.ht";

	ht = HT::Open(filename);

	ASSERT_NE(ht, nullptr);
	EXPECT_EQ(ht->Capacity, capacity);
	EXPECT_EQ(ht->SecSnapshotInterval, secSnapshotInterval);
	EXPECT_EQ(ht->MaxKeyLength, maxKeyLength);
	EXPECT_EQ(ht->MaxPayloadLength, maxPayloadLength);
	char pathname[MAX_PATH];
	GetFullPathNameA(filename, MAX_PATH, pathname, NULL);
	EXPECT_STREQ(ht->FileName, pathname);
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, Open_NotExisting_HT) {
	HT::HTHANDLE* ht = nullptr;
	int capacity = 1000;
	int secSnapshotInterval = 5;
	int maxKeyLength = 10;
	int maxPayloadLength = 100;
	LPCSTR filename = "..\\Test_HT_BAD.ht";

	ht = HT::Open(filename);

	ASSERT_EQ(ht, nullptr);
}

TEST(Test_HTAPI, Insert_Element) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "..\\Test_HT.ht";
	LPCSTR key = "testkey";
	int keylength = 8;
	LPCSTR payload = "testpayload";
	int payloadlength = 12;
	BOOL rc;
	HT::Element* element;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	rc = HT::Insert(ht, new HT::Element(key, keylength, payload, payloadlength));
	ASSERT_TRUE(rc);
	element = HT::Get(ht, new HT::Element(key, keylength));

	ASSERT_NE(element, nullptr);
	EXPECT_EQ(element->keylength, keylength);
	EXPECT_STREQ((LPSTR)element->key, key);
	EXPECT_EQ(element->payloadlength, payloadlength);
	EXPECT_STREQ((LPSTR)element->payload, payload);
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, NotInsert_Element_With_InvalidParameters) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "..\\Test_HT.ht";
	LPCSTR key = "testkey";
	int keylength = 100;
	LPCSTR payload = "testpayload";
	int payloadlength = 1000;
	BOOL rc;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	rc = HT::Insert(ht, new HT::Element(key, keylength, payload, payloadlength));

	ASSERT_FALSE(rc);
	EXPECT_STREQ(ht->LastErrorMessage, "Key length is greater then maximum key length!");
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, NotInsert_Element_When_Storage_Full) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "..\\Test_HT.ht";
	LPCSTR payload = "testpayload";
	int payloadlength = 12;
	BOOL rc;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	for (size_t i = 0; i < ht->Capacity; i++)
	{
		int startSize = ht->Size;
		char key[10];
		sprintf_s(key, "key%d", (int)i);
		int keylength = (int)strlen(key) + 1;
		rc = HT::Insert(ht, new HT::Element(key, keylength, payload, payloadlength));
		if (ht->Size == ht->Capacity && ht->Size == startSize) {
			ASSERT_FALSE(rc);
			EXPECT_STREQ(ht->LastErrorMessage, "Maximum capacity storage size reached!");
			break;
		}
		else
			ASSERT_TRUE(rc);
	}

	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, Update_Element) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "..\\Test_HT.ht";
	LPCSTR key = "testkey";
	int keylength = 8;
	LPCSTR payload = "newpayload";
	int payloadlength = 11;
	BOOL rc;
	HT::Element* element;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	rc = HT::Update(ht, new HT::Element(key, keylength), payload, payloadlength);
	ASSERT_TRUE(rc);
	element = HT::Get(ht, new HT::Element(key, keylength));

	ASSERT_NE(element, nullptr);
	EXPECT_EQ(element->keylength, keylength);
	EXPECT_STREQ((LPSTR)element->key, key);
	EXPECT_EQ(element->payloadlength, payloadlength);
	EXPECT_STREQ((LPSTR)element->payload, payload);
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, NotUpdate_NotExistingElement) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "..\\Test_HT.ht";
	LPCSTR key = "wrongkey";
	int keylength = 8;
	LPCSTR payload = "newpayload";
	int payloadlength = 11;
	BOOL rc;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	rc = HT::Update(ht, new HT::Element(key, keylength), payload, payloadlength);

	ASSERT_FALSE(rc);
	EXPECT_STREQ(ht->LastErrorMessage, "Element not found");
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, NotUpdate_Element_With_InvalidParameters) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "..\\Test_HT.ht";
	LPCSTR key = "testkey";
	int keylength = 8;
	LPCSTR payload = "newpayload";
	int payloadlength = 1000;
	BOOL rc;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	rc = HT::Update(ht, new HT::Element(key, keylength), payload, payloadlength);

	ASSERT_FALSE(rc);
	EXPECT_STREQ(ht->LastErrorMessage, "Payload length is greater then maximum payload length!");
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, Delete_Element) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "..\\Test_HT.ht";
	LPCSTR key = "testkey";
	int keylength = 8;
	BOOL rc;
	HT::Element* element;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	rc = HT::Delete(ht, new HT::Element(key, keylength));
	ASSERT_TRUE(rc);
	element = HT::Get(ht, new HT::Element(key, keylength));

	ASSERT_EQ(element, nullptr);
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, NotDelete_NotExistingElement) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "..\\Test_HT.ht";
	LPCSTR key = "wrongkey";
	int keylength = 9;
	BOOL rc;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	rc = HT::Delete(ht, new HT::Element(key, keylength));

	ASSERT_FALSE(rc);
	EXPECT_STREQ(ht->LastErrorMessage, "Element not found");
	ASSERT_TRUE(HT::Close(ht));
}