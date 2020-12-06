/*
--- Day 4: Passport Processing ---
You arrive at the airport only to realize that you grabbed your North Pole Credentials instead of your passport. While these documents are extremely similar, North Pole Credentials aren't issued by a country and therefore aren't actually valid documentation for travel in most of the world.

It seems like you're not the only one having problems, though; a very long line has formed for the automatic passport scanners, and the delay could upset your travel itinerary.

Due to some questionable network security, you realize you might be able to solve both of these problems at the same time.

The automatic passport scanners are slow because they're having trouble detecting which passports have all required fields. The expected fields are as follows:

byr (Birth Year)
iyr (Issue Year)
eyr (Expiration Year)
hgt (Height)
hcl (Hair Color)
ecl (Eye Color)
pid (Passport ID)
cid (Country ID)
Passport data is validated in batch files (your puzzle input). Each passport is represented as a sequence of key:value pairs separated by spaces or newlines. Passports are separated by blank lines.

Here is an example batch file containing four passports:

ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
byr:1937 iyr:2017 cid:147 hgt:183cm

iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
hcl:#cfa07d byr:1929

hcl:#ae17e1 iyr:2013
eyr:2024
ecl:brn pid:760753108 byr:1931
hgt:179cm

hcl:#cfa07d eyr:2025 pid:166559648
iyr:2011 ecl:brn hgt:59in
The first passport is valid - all eight fields are present. The second passport is invalid - it is missing hgt (the Height field).

The third passport is interesting; the only missing field is cid, so it looks like data from North Pole Credentials, not a passport at all! Surely, nobody would mind if you made the system temporarily ignore missing cid fields. Treat this "passport" as valid.

The fourth passport is missing two fields, cid and byr. Missing cid is fine, but missing any other field is not, so this passport is invalid.

According to the above rules, your improved system would report 2 valid passports.

Count the number of valid passports - those that have all required fields. Treat cid as optional. In your batch file, how many passports are valid?

Your puzzle answer was 216.

--- Part Two ---
The line is moving more quickly now, but you overhear airport security talking about how passports with invalid data are getting through. Better add some data validation, quick!

You can continue to ignore the cid field, but each other field has strict rules about what values are valid for automatic validation:

byr (Birth Year) - four digits; at least 1920 and at most 2002.
iyr (Issue Year) - four digits; at least 2010 and at most 2020.
eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
hgt (Height) - a number followed by either cm or in:
If cm, the number must be at least 150 and at most 193.
If in, the number must be at least 59 and at most 76.
hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
pid (Passport ID) - a nine-digit number, including leading zeroes.
cid (Country ID) - ignored, missing or not.
Your job is to count the passports where all required fields are both present and valid according to the above rules. Here are some example values:

byr valid:   2002
byr invalid: 2003

hgt valid:   60in
hgt valid:   190cm
hgt invalid: 190in
hgt invalid: 190

hcl valid:   #123abc
hcl invalid: #123abz
hcl invalid: 123abc

ecl valid:   brn
ecl invalid: wat

pid valid:   000000001
pid invalid: 0123456789
Here are some invalid passports:

eyr:1972 cid:100
hcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 byr:1926

iyr:2019
hcl:#602927 eyr:1967 hgt:170cm
ecl:grn pid:012533040 byr:1946

hcl:dab227 iyr:2012
ecl:brn hgt:182cm pid:021572410 eyr:2020 byr:1992 cid:277

hgt:59cm ecl:zzz
eyr:2038 hcl:74454a iyr:2023
pid:3556412378 byr:2007
Here are some valid passports:

pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980
hcl:#623a2f

eyr:2029 ecl:blu cid:129 byr:1989
iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm

hcl:#888785
hgt:164cm byr:2001 iyr:2015 cid:88
pid:545766238 ecl:hzl
eyr:2022

iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719
Count the number of valid passports - those that have all required fields and valid values. Continue to treat cid as optional. In your batch file, how many passports are valid?

Your puzzle answer was 150.
*/
#include "advent.h"

typedef struct {
	char eyr[20];
	char byr[20];
	char iyr[20];
	char pid[20];
	char cid[20];
	char ecl[20];
	char hcl[20];
	char hgt[20];
} Pass;

static Pass *arr;
static int cnt;

static void newArrEntry(){
	arr = realloc(arr, ++cnt * sizeof(Pass));
	strcpy(arr[cnt-1].eyr , "");
	strcpy(arr[cnt-1].byr , "");
	strcpy(arr[cnt-1].iyr , "");
	strcpy(arr[cnt-1].pid , "");
	strcpy(arr[cnt-1].cid , "");
	strcpy(arr[cnt-1].ecl , "");
	strcpy(arr[cnt-1].hcl , "");
	strcpy(arr[cnt-1].hgt , "");
}

/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
	size_t l;
	arr = NULL;
	cnt = 0;
   
	FILE *file = fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}

	newArrEntry();
	while( getline(&line, &l, file) != -1) {
		
		if(strcmp(trim(line), "") == 0){
			newArrEntry();
			continue;
		}

		char *end_str;
		char *pt1 = strtok_r(line, " ", &end_str);

		while(pt1) {

			char *end_token;
			char *pt2 = strtok_r(pt1, ":", &end_token);

			if(pt2) {
				if(strcmp(pt2,"byr") == 0) {
					pt2 = strtok_r(NULL, ":", &end_token);
					strcpy(arr[cnt-1].byr, pt2);
				}
				else if(strcmp(pt2,"eyr") == 0) {
					pt2 = strtok_r(NULL, ":", &end_token);
					strcpy(arr[cnt-1].eyr, pt2);
				}
				else if(strcmp(pt2,"iyr") == 0) {
					pt2 = strtok_r(NULL, ":", &end_token);
					strcpy(arr[cnt-1].iyr, pt2);
				}
				else if(strcmp(pt2,"hgt") == 0) {
					pt2 = strtok_r(NULL, ":", &end_token);
					strcpy(arr[cnt-1].hgt, pt2);
				}
				else if(strcmp(pt2,"ecl") == 0) {
					pt2 = strtok_r(NULL, ":", &end_token);
					strcpy(arr[cnt-1].ecl, pt2);
				}
				else if(strcmp(pt2,"hcl") == 0) {
					pt2 = strtok_r(NULL, ":", &end_token);
					strcpy(arr[cnt-1].hcl, pt2);
				}
				else if(strcmp(pt2,"pid") == 0) {
					pt2 = strtok_r(NULL, ":", &end_token);
					strcpy(arr[cnt-1].pid, pt2);
				}
				else if(strcmp(pt2,"cid") == 0) {
					pt2 = strtok_r(NULL, ":", &end_token);
					strcpy(arr[cnt-1].cid, pt2);
				}
			}
			pt1 = strtok_r(NULL, " ", &end_str);
		}
	}

	free(line);
	fclose(file);
	return 1;
}

/*##########################
# Function to solve part A #
##########################*/
void get4a(char * f) {
	if(!getInput(f))
		return;

	int result = 0;
	for (int i = 0; i < cnt; i++) {
		if( strcmp(arr[i].byr,"") != 0 && strcmp(arr[i].iyr,"") != 0 && strcmp(arr[i].eyr,"") != 0 &&
			strcmp(arr[i].hcl,"") != 0 && strcmp(arr[i].ecl,"") != 0 && strcmp(arr[i].pid,"") != 0 && strcmp(arr[i].hgt,"") != 0)
			result++;
	}

	printf("4a: %d\n", result);
	free(arr);
}


/*##########################
# Function to solve part B #
##########################*/
void get4b(char *f) {
	if(!getInput(f))
		return;

	int result = 0;

	for (int i = 0; i < cnt; i++) {
		if( strcmp(arr[i].byr,"") != 0 && strcmp(arr[i].iyr,"") != 0 &&
			strcmp(arr[i].eyr,"") != 0 && strcmp(arr[i].hcl,"") != 0 && 
			strcmp(arr[i].ecl,"") != 0 && strcmp(arr[i].pid,"") != 0 && 
			strcmp(arr[i].hgt,"") != 0)
		{

			int byr = toI(arr[i].byr);
			int iyr = toI(arr[i].iyr);
			int eyr = toI(arr[i].eyr);

			int ecl = 0;
			if( strcmp(arr[i].ecl,"amb") == 0 || strcmp(arr[i].ecl,"blu") == 0 || strcmp(arr[i].ecl,"brn") == 0 ||
				strcmp(arr[i].ecl,"gry") == 0 || strcmp(arr[i].ecl,"grn") == 0 || strcmp(arr[i].ecl,"hzl") == 0 || strcmp(arr[i].ecl,"oth") == 0)
			{
				ecl = 1;
			}

			int hcl = 0;
			if(strlen(arr[i].hcl) == 7 && arr[i].hcl[0] == '#') {
				hcl = 1;
				for(int k = 1; k < 7; k++) {
					if(!isHexDigit(arr[i].hcl[k])) {
						hcl = 0;
						break;
					}
				}
			}

			int pid = 0;
			if(strlen(arr[i].pid) == 9){
				pid = 1;
				for(int k = 0; k < 9; k++) {
					if(!isDigit(arr[i].pid[k])) {
						pid = 0;
						break;
					}
				}
			}

			int hgt = 0;
			char *end = arr[i].hgt + (strlen(arr[i].hgt)-2);
			if(strcmp(end,"in") == 0){
				*end = '\0';
				int height = toI(arr[i].hgt);
				if(height >= 59 && height <= 76)
					hgt = 1;
			}
			else if(strcmp(end,"cm") == 0){
				*end = '\0';
				int height = toI(arr[i].hgt);
				if(height >= 150 && height <= 193)
					hgt = 1;
			}

			if( byr >= 1920 && byr <= 2002 &&
				eyr >= 2020 && eyr <= 2030 &&
				iyr >= 2010 && iyr <= 2020 &&
				hcl == 1 && ecl == 1 && pid == 1 && hgt == 1)
				result++;


		}
	}

	printf("4b: %d\n\n", result);
	free(arr);
}