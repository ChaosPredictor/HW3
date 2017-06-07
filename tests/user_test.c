#include "./user_test.h"

/*
static bool testCopyUser() {

	ASSERT_TEST( copyUser(NULL) == NULL);

	User user = malloc(sizeof(struct user_t));
	char* email = "qazxsw@edcvfr";
	user->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(user->email, email);
	user->faculty = CIVIL_ENGINEERING;

	User newUser = copyUser(user);

	ASSERT_TEST( newUser != NULL);
	ASSERT_TEST( strcmp(user->email,newUser->email) == 0);
	ASSERT_TEST( user->faculty == newUser->faculty );

	free(newUser->email);
	free(newUser);

	free(user->email);
	free(user);

	return true;
}

static bool testFreeUser() {

	//ASSERT_TEST( freeCompany(NULL) == NULL);
	freeUser(NULL);

	User user = malloc(sizeof(struct user_t));
	char* email = "qazxsw@edcvfr";
	user->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(user->email, email);
	user->faculty = CIVIL_ENGINEERING;

	User newUser = copyUser(user);

	freeUser(newUser);
	freeUser(user);

	return true;
}

static bool testCompareUser() {

	ASSERT_TEST( copyUser(NULL) == NULL);

	User user = malloc(sizeof(struct user_t));
	char* email = "qazxsw@edcvfr";
	user->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(user->email, email);
	user->faculty = CIVIL_ENGINEERING;

	User newUser = copyUser(user);

	ASSERT_TEST( newUser != NULL);
	ASSERT_TEST( strcmp(user->email,newUser->email) == 0);
	ASSERT_TEST( user->faculty == newUser->faculty );

	ASSERT_TEST( compareUsers(user, newUser) == 0 );

	char* email2 = "qazxsw@edcvfp";
	free(user->email);
	user->email = malloc(sizeof(char) * (strlen(email2) + 1));
	strcpy(user->email, email2);

	ASSERT_TEST( compareUsers(user, newUser) != 0 );

	free(newUser->email);
	free(newUser);

	free(user->email);
	free(user);

	return true;
}
*/
static bool testAddUser() {
/*
	Set users = setCreate(copyUser, freeUser, compareUsers);
	ASSERT_TEST( users != NULL);
	ASSERT_TEST( setGetSize(users) == 0 );

	//Invalid parameters
	ASSERT_TEST( addUser(NULL, "company1@civil", CIVIL_ENGINEERING, COMPANY ) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(users) == 0 );
	ASSERT_TEST( addUser(users, NULL, CIVIL_ENGINEERING, COMPANY ) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(users) == 0 );
	ASSERT_TEST( addUser(users, "company1@civil", CIVIL_ENGINEERING, 11 ) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(users) == 0 );
	ASSERT_TEST( addUser(users, "company1@civil", CIVIL_ENGINEERING, -1 ) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(users) == 0 );
	ASSERT_TEST( addUser(users, "company1@civil", CIVIL_ENGINEERING, 18 ) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(users) == 0 );
	ASSERT_TEST( addUser(users, "company1@civil", CIVIL_ENGINEERING, -1 ) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(users) == 0 );
	//Invalid email
	ASSERT_TEST( addUser(users, "company1#civil", CIVIL_ENGINEERING, COMPANY ) == MTM_INVALID_PARAMETER);
	ASSERT_TEST( setGetSize(users) == 0 );

	//success company
	ASSERT_TEST( addUser(users, "company1@civil", CIVIL_ENGINEERING, COMPANY ) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(users) == 1 );
	//fail - same email
	ASSERT_TEST( addUser(users, "company1@civil", CIVIL_ENGINEERING, COMPANY ) == MTM_EMAIL_ALREADY_EXISTS );
	ASSERT_TEST( setGetSize(users) == 1 );
	ASSERT_TEST( addUser(users, "company1@civil", MECHANICAL_ENGINEERING, COMPANY ) == MTM_EMAIL_ALREADY_EXISTS );
	ASSERT_TEST( setGetSize(users) == 1 );
	ASSERT_TEST( addUser(users, "company1@civil", CIVIL_ENGINEERING,  ESCAPER_2 ) == MTM_EMAIL_ALREADY_EXISTS );
	ASSERT_TEST( setGetSize(users) == 1 );
	ASSERT_TEST( addUser(users, "company1@civil", MECHANICAL_ENGINEERING,  ESCAPER_2 ) == MTM_EMAIL_ALREADY_EXISTS );
	ASSERT_TEST( setGetSize(users) == 1 );
	//success other company same faculty
	ASSERT_TEST( addUser(users, "company2@civil", CIVIL_ENGINEERING, COMPANY ) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(users) == 2 );
	//success escaper
	ASSERT_TEST( addUser(users, "escaper1@civil", CIVIL_ENGINEERING, ESCAPER_1 ) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(users) == 3 );
	//same email
	ASSERT_TEST( addUser(users, "escaper1@civil", MECHANICAL_ENGINEERING, ESCAPER_1 ) == MTM_EMAIL_ALREADY_EXISTS );
	ASSERT_TEST( setGetSize(users) == 3 );
	ASSERT_TEST( addUser(users, "escaper1@civil", CIVIL_ENGINEERING, ESCAPER_2 ) == MTM_EMAIL_ALREADY_EXISTS );
	ASSERT_TEST( setGetSize(users) == 3 );
	ASSERT_TEST( addUser(users, "escaper1@civil", MECHANICAL_ENGINEERING, ESCAPER_2 ) == MTM_EMAIL_ALREADY_EXISTS );
	ASSERT_TEST( setGetSize(users) == 3 );
	//success escaper
	ASSERT_TEST( addUser(users, "escaper2@civil", CIVIL_ENGINEERING, ESCAPER_1 ) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(users) == 4 );
	ASSERT_TEST( addUser(users, "escaper4@electrical", ELECTRICAL_ENGINEERING, ESCAPER_10 ) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(users) == 5 );

	setClear(users);
	ASSERT_TEST( setGetSize(users) == 0 );
	setDestroy(users);
*/
	return true;
}

Set testHelperAddUsers() {

	Set escapers = setCreate(copyEscaper, freeEscaper, compareEscapers);
	/*ASSERT_TEST( users != NULL);

	addUser( users, "company1@civil", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "company2@civil", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "company3@civil", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "company5@civil", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "company1@mechanical", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "company2@mechanical", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "company3@mechanical", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "company4@mechanical", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "company6@mechanical", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "company1@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company2@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company3@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company5@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company6@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company7@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company1@chemical", CHEMICAL_ENGINEERING, COMPANY );
	addUser( users, "company1@biotechnology", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, COMPANY );
	addUser( users, "company1@aerospace", AEROSPACE_ENGINEERING, COMPANY );
	addUser( users, "company1@industrial", INDUSTRIAL_ENGINEERING_AND_MANAGEMENT, COMPANY );
	addUser( users, "company1@mathematics", MATHEMATICS, COMPANY );
	addUser( users, "company1@physics", PHYSICS, COMPANY );
	addUser( users, "company1@chemistry", CHEMISTRY, COMPANY );
	addUser( users, "company1@biology", BIOLOGY, COMPANY );
	addUser( users, "company1@architecture", ARCHITECTURE, COMPANY );
	addUser( users, "company1@education", EDUCATION_IN_TECH_AND_SCIENCE, COMPANY );
	addUser( users, "company1@computer", COMPUTER_SCIENCE, COMPANY );
	addUser( users, "company1@medicine", MEDICINE, COMPANY );
	addUser( users, "company1@materials", MATERIALS_ENGINEERING, COMPANY );
	addUser( users, "company1@humanites", HUMANITIES_AND_ARTS, COMPANY );
	addUser( users, "company1@biomedical", BIOMEDICAL_ENGINEERING, COMPANY );
	addUser( users, "escaper1@civil", CIVIL_ENGINEERING, ESCAPER_1 );
	addUser( users, "escaper2@civil", CIVIL_ENGINEERING, ESCAPER_5 );
	addUser( users, "escaper3@mechanical", MECHANICAL_ENGINEERING, ESCAPER_2 );
	addUser( users, "escaper1@mechanical", MECHANICAL_ENGINEERING, ESCAPER_8 );
	addUser( users, "escaper1@electrical", ELECTRICAL_ENGINEERING, ESCAPER_10 );
	addUser( users, "escaper2@electrical", ELECTRICAL_ENGINEERING, ESCAPER_6 );
	addUser( users, "escaper1@physics", PHYSICS, ESCAPER_6 );
	addUser( users, "escaper1@biotechnology", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, ESCAPER_1 );
	addUser( users, "escaper1@aerospace", AEROSPACE_ENGINEERING, ESCAPER_7 );
	addUser( users, "escaper1@education", EDUCATION_IN_TECH_AND_SCIENCE, ESCAPER_9 );
	addUser( users, "escaper1@mathematics", MATHEMATICS, ESCAPER_7 );


	ASSERT_TEST( setGetSize(users) == 41 );*/
	return escapers;
}

static bool testRemoveCompany() {

	Set users = testHelperAddUsers();
/*
	int numberOfUsers = setGetSize(users);
	//invalid email
	ASSERT_TEST( removeCompany( users, NULL ) ==  MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );
	ASSERT_TEST( removeCompany( users, "company2#civil" ) ==  MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );
	//company email does not exist
	ASSERT_TEST( removeCompany( users, "company9@civil" ) ==  MTM_COMPANY_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );
	//escaper email
	ASSERT_TEST( removeCompany( users, "escaper1@civil" ) ==  MTM_COMPANY_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );
	//TODO company with order

	ASSERT_TEST( removeCompany( users, "company2@civil" ) ==  MTM_SUCCESS );
	numberOfUsers--;
	ASSERT_TEST( setGetSize(users) == numberOfUsers );

	ASSERT_TEST( removeCompany( users, "escaper1@civil" ) ==  MTM_COMPANY_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );

	ASSERT_TEST( removeCompany( users, "company2@civil" ) ==  MTM_COMPANY_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );

	setClear(users);

	ASSERT_TEST( setGetSize(users) == 0 );*/
	setDestroy(users);
	return true;
}



static bool testRemoveEscaper() {
	//TODO
	Set users = testHelperAddUsers();
/*
	int numberOfUsers = setGetSize(users);

	ASSERT_TEST( removeEscaper( NULL, "escaper1@civil" ) ==  MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );
	//invalid email
	ASSERT_TEST( removeEscaper( users, NULL ) ==  MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );
	ASSERT_TEST( removeEscaper( users, "escaper1#civil" ) ==  MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );
	//escaper email does not exist
	ASSERT_TEST( removeEscaper( users, "escaper11@civil" ) ==  MTM_CLIENT_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );
	//escaper email
	ASSERT_TEST( removeEscaper( users, "company1@civil" ) ==  MTM_CLIENT_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );
	//TODO company with order

	ASSERT_TEST( removeEscaper( users, "escaper1@civil" ) ==  MTM_SUCCESS );
	numberOfUsers--;
	ASSERT_TEST( setGetSize(users) == numberOfUsers );

	ASSERT_TEST( removeEscaper( users, "escaper1@civil" ) ==  MTM_CLIENT_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( setGetSize(users) == numberOfUsers );

	setClear(users);

	ASSERT_TEST( setGetSize(users) == 0 );*/
	setDestroy(users);
	return true;
}


static bool testFindCompanyFacultyFromEmail() {
/*
	Set users = setCreate(copyEscaper freeUser, compareUsers);
	ASSERT_TEST( users != NULL);

	ASSERT_TEST( setGetSize(users) == 0 );

	addUser( users, "sdfefdgdfh565@654fgjhfgsda", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdb", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdc", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdd", CHEMICAL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsde", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdf", AEROSPACE_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdg", INDUSTRIAL_ENGINEERING_AND_MANAGEMENT, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdh", MATHEMATICS, COMPANY );

	ASSERT_TEST( findCompanyFacultyFromEmail(NULL, NULL) == UNKNOWN);
	ASSERT_TEST( findCompanyFacultyFromEmail(NULL, "sdfefdgdfh565@654fgjhfgsd0") == UNKNOWN);
	ASSERT_TEST( findCompanyFacultyFromEmail(users, NULL) == UNKNOWN);

	ASSERT_TEST( findCompanyFacultyFromEmail(users, "sdfefdgdfh565@654fgjhfgsda") == CIVIL_ENGINEERING);
	ASSERT_TEST( findCompanyFacultyFromEmail(users, "sdfefdgdfh565@654fgjhfgsdb") == MECHANICAL_ENGINEERING);
	ASSERT_TEST( findCompanyFacultyFromEmail(users, "sdfefdgdfh565@654fgjhfgsdc") == ELECTRICAL_ENGINEERING);
	ASSERT_TEST( findCompanyFacultyFromEmail(users, "sdfefdgdfh565@654fgjhfgsdd") == CHEMICAL_ENGINEERING);
	ASSERT_TEST( findCompanyFacultyFromEmail(users, "sdfefdgdfh565@654fgjhfgsde") == BIOTECHNOLOGY_AND_FOOD_ENGINEERING);
	ASSERT_TEST( findCompanyFacultyFromEmail(users, "sdfefdgdfh565@654fgjhfgsdf") == AEROSPACE_ENGINEERING);
	ASSERT_TEST( findCompanyFacultyFromEmail(users, "sdfefdgdfh565@654fgjhfgsdg") == INDUSTRIAL_ENGINEERING_AND_MANAGEMENT);
	ASSERT_TEST( findCompanyFacultyFromEmail(users, "sdfefdgdfh565@654fgjhfgsdh") == MATHEMATICS);
	ASSERT_TEST( findCompanyFacultyFromEmail(users, "sdfefdgdfh565@654fgjhfgsd0") == UNKNOWN);

	setDestroy(users);*/

	return true;
}

static bool testEmailValidity() {
	ASSERT_TEST( emailValidity("45@$#") );
	ASSERT_TEST( !emailValidity("45^$#") );
	ASSERT_TEST( !emailValidity("45@@#") );
	return true;
}

static bool testOtherSetUserFunctions() {
	/*
	Set users = setCreate(copyUser, freeUser, compareUsers);
	ASSERT_TEST( users != NULL );

	User user1 = malloc(sizeof(struct user_t));
	char* email1 = "sdf@fdgdfh56";
	user1->email = malloc(sizeof(char) * (strlen(email1) + 1));
	strcpy(user1->email, email1);
	user1->faculty = CIVIL_ENGINEERING;

	User user2 = malloc(sizeof(struct user_t));
	char* email2 = "sdf@fdgdfh57";
	user2->email = malloc(sizeof(char) * (strlen(email2) + 1));
	strcpy(user2->email, email2);
	user2->faculty = CIVIL_ENGINEERING;

	User user3 = malloc(sizeof(struct user_t));
	char* email3 = "sdf@fdgdfh58";
	user3->email = malloc(sizeof(char) * (strlen(email3) + 1));
	strcpy(user3->email, email1);
	user3->faculty = CIVIL_ENGINEERING;

	User user4 = malloc(sizeof(struct user_t));
	char* email4 = "sdf@fdgdfh59";
	user4->email = malloc(sizeof(char) * (strlen(email4) + 1));
	strcpy(user4->email, email1);
	user4->faculty = CIVIL_ENGINEERING;

	addUser(users, "sdf@fdgdfh56", CIVIL_ENGINEERING, COMPANY);
	addUser(users, "sdf@fdgdfh57", CIVIL_ENGINEERING, COMPANY);
	addUser(users, "sdf@fdgdfh58", CIVIL_ENGINEERING, COMPANY);
	addUser(users, "sdf@fdgdfh59", CIVIL_ENGINEERING, COMPANY);

	ASSERT_TEST( setGetSize(users) == 4 );

	ASSERT_TEST( setIsIn(users, user1) );
	ASSERT_TEST( setIsIn(users, user2) );
	ASSERT_TEST( setIsIn(users, user3) );
	ASSERT_TEST( setIsIn(users, user4) );

	Set newUsers = setCopy(users);

	ASSERT_TEST( setIsIn(newUsers, user1) );
	ASSERT_TEST( setIsIn(newUsers, user2) );
	ASSERT_TEST( setIsIn(newUsers, user3) );
	ASSERT_TEST( setIsIn(newUsers, user4) );


	ASSERT_TEST( setGetSize(newUsers) == 4 );

	freeUser(user1);
	freeUser(user2);
	freeUser(user3);
	freeUser(user4);
	setDestroy(users);
	setDestroy(newUsers);*/
	return true;
}

int userTests (int argv, char** arc){
	//RUN_TEST(testCopyUser);
	//RUN_TEST(testFreeUser);
	//RUN_TEST(testCompareUser);
	RUN_TEST(testAddUser);
	RUN_TEST(testRemoveCompany);
	RUN_TEST(testRemoveEscaper);
	RUN_TEST(testEmailValidity);
	RUN_TEST(testFindCompanyFacultyFromEmail);
	RUN_TEST(testOtherSetUserFunctions);
	return 0;
}
