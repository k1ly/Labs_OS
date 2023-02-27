#include "pch.h"
#include "OS10_HTAPI.h"

TEST(Test_HTAPI, Create_HT) {
	HT::HTHANDLE* ht = nullptr;
	DWORD capacity = 1000;
	DWORD secSnapshotInterval = 5;
	DWORD maxKeyLength = 10;
	DWORD maxPayloadLength = 100;
	LPCSTR filename = "C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab10\\Test_HT.ht";

	ht = HT::Create(capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, filename);

	ASSERT_NE(ht, nullptr);
	EXPECT_EQ(ht->Capacity, capacity);
	EXPECT_EQ(ht->SecSnapshotInterval, secSnapshotInterval);
	EXPECT_EQ(ht->MaxKeyLength, maxKeyLength);
	EXPECT_EQ(ht->MaxPayloadLength, maxPayloadLength);
	EXPECT_STREQ(ht->FileName, filename);

	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, NotCreate_HT_With_InvalidParameters) {
	HT::HTHANDLE* ht = nullptr;
	DWORD capacity = -1000;
	DWORD secSnapshotInterval = -5;
	DWORD maxKeyLength = -10;
	DWORD maxPayloadLength = -100;

	ht = HT::Create(capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, nullptr);

	ASSERT_EQ(ht, nullptr);
}

TEST(Test_HTAPI, Open_HT) {
	HT::HTHANDLE* ht = nullptr;
	DWORD capacity = 1000;
	DWORD secSnapshotInterval = 5;
	DWORD maxKeyLength = 10;
	DWORD maxPayloadLength = 100;
	LPCSTR filename = "C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab10\\Test_HT.ht";

	ht = HT::Open(filename);

	ASSERT_NE(ht, nullptr);
	EXPECT_EQ(ht->Capacity, capacity);
	EXPECT_EQ(ht->SecSnapshotInterval, secSnapshotInterval);
	EXPECT_EQ(ht->MaxKeyLength, maxKeyLength);
	EXPECT_EQ(ht->MaxPayloadLength, maxPayloadLength);
	EXPECT_STREQ(ht->FileName, filename);
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, Insert_Element) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab10\\Test_HT.ht";
	LPCSTR key = "testkey";
	DWORD keylength = 8;
	LPCSTR payload = "testpayload";
	DWORD payloadlength = 12;
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
	EXPECT_STREQ((LPCSTR)element->payload, payload);
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, NotInsert_Element_With_InvalidParameters) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab10\\Test_HT.ht";
	LPCSTR key = "testkey";
	DWORD keylength = 100;
	LPCSTR payload = "testpayload";
	DWORD payloadlength = 1000;
	BOOL rc;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	rc = HT::Insert(ht, new HT::Element(key, keylength, payload, payloadlength));

	ASSERT_FALSE(rc);
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, Update_Element) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab10\\Test_HT.ht";
	LPCSTR key = "testkey";
	DWORD keylength = 8;
	LPCSTR payload = "newpayload";
	DWORD payloadlength = 11;
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
	EXPECT_STREQ((LPCSTR)element->payload, payload);
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, NotUpdate_NotExistingElement) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab10\\Test_HT.ht";
	LPCSTR key = "wrongkey";
	DWORD keylength = 8;
	LPCSTR payload = "newpayload";
	DWORD payloadlength = 11;
	BOOL rc;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	rc = HT::Update(ht, new HT::Element(key, keylength), payload, payloadlength);

	ASSERT_FALSE(rc);
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, NotUpdate_Element_With_InvalidParameters) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab10\\Test_HT.ht";
	LPCSTR key = "testkey";
	DWORD keylength = 8;
	LPCSTR payload = "newpayload";
	DWORD payloadlength = 1000;
	BOOL rc;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	rc = HT::Update(ht, new HT::Element(key, keylength), payload, payloadlength);

	ASSERT_FALSE(rc);
	ASSERT_TRUE(HT::Close(ht));
}

TEST(Test_HTAPI, Delete_Element) {
	HT::HTHANDLE* ht = nullptr;
	LPCSTR filename = "C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab10\\Test_HT.ht";
	LPCSTR key = "testkey";
	DWORD keylength = 8;
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
	LPCSTR filename = "C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab10\\Test_HT.ht";
	LPCSTR key = "wrongkey";
	DWORD keylength = 9;
	BOOL rc;

	ht = HT::Open(filename);
	ASSERT_NE(ht, nullptr);
	rc = HT::Delete(ht, new HT::Element(key, keylength));

	ASSERT_FALSE(rc);
	ASSERT_TRUE(HT::Close(ht));
}