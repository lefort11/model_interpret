#include "testing.h"
#include "../String.h"

TEST(stringEquals)
		{
			String string1 = "hui";
			String string2 = "hui";
			String string3 = "pizda";
			String string4 = "";
			assert(string1 == string2);
			assert(string1 != string3);
			assert(string4.IsEmpty());
		};

TEST(stringConcat)
		{
			String string1 = "hui";
			String string2 = "Olega";
			string1 += string2;
			assert(string1 == String("huiOlega"));
			assert(string1.GetLength() == 8);
			assert(string1.GetBufSize() == 9);
			String string3(10, 0);
			assert(string3.GetLength() == 0);
			assert(string3.GetBufSize() == 10);
			assert(string3.IsEmpty());
		};

TEST(stringClear)
		{
			String string1 = "Oleg hui";
			string1.Clear();
			assert(string1.IsEmpty());
		};

TEST(stringCopyConstruhter)
		{
			String string1 = "OLEG HUI";
			String string2(string1);
			string1.Clear();
			assert(string2 == String("OLEG HUI"));

		};

TEST(stringAssignOperator)
		{
			String string1 = "OLEG HUI";
			String string2;
			string2 = string1;
			string1.Clear();
			assert(string2 == String("OLEG HUI"));
		};
