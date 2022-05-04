#include "SqliteDatabase.h"




SqliteDatabase::SqliteDatabase() {

	
	int doesntExist = _access(DB_NAME_SQLITE, 0);

	int res = sqlite3_open(DB_NAME_SQLITE, &db);
	if (res != SQLITE_OK) {
		db = nullptr;
		std::cerr << "Failed to open DB" << std::endl;
	}


	if (doesntExist) {
		setupDb();
	}
}



/* 
setup function for the database for when the database file is first created
It creates the following tables:
Users containing: Username(Text), Password(Text), Email(Text)
*/
void SqliteDatabase::setupDb() {

	std::string createQuery;
	char* errMsg = nullptr;
	int queryRes = 0;

	// Users table creation
	createQuery = "CREATE TABLE Users (\nUsername TEXT,\nPassword TEXT NOT NULL,\nEmail TEXT NOT NULL UNIQUE,\nPRIMARY KEY(Username));";
	queryRes = sqlite3_exec(db, createQuery.c_str(), nullptr, nullptr, &errMsg);

	if (queryRes != SQLITE_OK) {
		std::cerr << "An error has occured: " << errMsg << std::endl;
		_exit(1);
	}


	createQuery = "CREATE TABLE Questions (\nId INTEGER,\nQuestion TEXT NOT NULL UNIQUE,\CorrectAnswer TEXT NOT NULL,\nAnswer2 TEXT NOT NULL,\nAnswer3 TEXT NOT NULL,\nAnswer4 NUMERIC NOT NULL,\nPRIMARY KEY(Id AUTOINCREMENT));";
	queryRes = sqlite3_exec(db, createQuery.c_str(), nullptr, nullptr, &errMsg);

	if (queryRes != SQLITE_OK) {
		std::cerr << "An error has occured: " << errMsg << std::endl;
		_exit(1);
	}

	createQuery = "INSERT INTO Questions\n(Question, CorrectAnswer, Answer2, Answer3, Answer4)\nVALUES ('What tool lends its name to a last - stone advantage in an end in Curling ? ', 'Hammer', 'Wrench', 'Drill', 'Screwdriver'),\n('On a standard Monopoly board, which square is diagonally opposite Go? ', 'Free Parking', 'Go to Jail', 'Jail', 'The Electric Company'),\n('What is the capital of Denmark?', 'Copenhagen', 'Aarhus', 'Odense', 'Aalborg'),\n('Who is the leader of Team Instinct in Pokemon Go?', 'Spark', 'Candela', 'Blanche', 'Willow'),\n('Which issue of the \"Sonic the Hedgehog\" comic did Scourge the Hedgehog make his first appearance?', 'Sonic the Hedgehog #11', 'Sonic Universe #32', 'Sonic the Hedgehog #161', 'Sonic the Hedgehog #47'),\n('What does a funambulist walk on?', 'A Tight Rope', 'Broken Glass', 'Balls', 'The Moon'),\n('What year was the Disney film \"A Goofy Movie\" released?', '1995', '1999', '2001', '1997'),\n('Which of these book series is by James Patterson?', 'Maximum Ride', 'Harry Potter', 'The Legend of Xanth', 'The Bartemaeus Trilogy'),\n('Who out of these actresses is the youngest?', 'Kiernan Shipka', 'Ariel Winter', 'Emma Watson', 'Bonnie Wright'),\n('Broome is a town in which state of Australia?', 'Western Australia', 'Northern Territory', 'South Australia', 'Tasmania'),\n('What is the name of the planet that the Doctor from television series \"Doctor Who\" comes from?', 'Gallifrey', 'Sontar', 'Skaro', 'Mondas'),\n('Which animation studio animated \"Psycho Pass\"?', 'Production I.G', 'Kyoto Animation', 'Shaft', 'Trigger'),\n('In Mulan (1998), who is the leader of the Huns?', 'Shan Yu', 'Chien-Po', 'Li Shang', 'Fa Zhou'),\n('Who directed the Kill Bill movies?', 'Quentin Tarantino', 'Arnold Schwarzenegger', 'David Lean', 'Stanley Kubrick'),\n('What is the birth name of Michael Caine?', 'Maurice Micklewhite', 'Morris Coleman', 'Carl Myers', 'Martin Michaels');";
	queryRes = sqlite3_exec(db, createQuery.c_str(), nullptr, nullptr, &errMsg);

	if (queryRes != SQLITE_OK) {
		std::cout << "here" << std::endl;
		std::cerr << "An error has occured: " << errMsg << std::endl;
		_exit(1);
	}



	createQuery = "CREATE TABLE Stats (\nUsername TEXT NOT NULL UNIQUE,\nCorrectAnswers INTEGER NOT NULL,\nTotalAnswers INTEGER NOT NULL,\nAverageAnswerTime REAL NOT NULL,\nTotalGames INTEGER NOT NULL,\nFOREIGN KEY(Username) REFERENCES Users(Username)\n);";
	queryRes = sqlite3_exec(db, createQuery.c_str(), nullptr, nullptr, &errMsg);

	if (queryRes != SQLITE_OK) {
		std::cout << "here" << std::endl;
		std::cerr << "An error has occured: " << errMsg << std::endl;
		_exit(1);
	}


}



// Inserts a new user to the DB with the provided and needed info (check Users table setup for more info)
void SqliteDatabase::addNewUser(std::string newUsername, std::string newPassword, std::string newEmail) {

	std::string insertQuery = "INSERT INTO Users\n(Username, Password, Email)\nVALUES(\n'" + newUsername + "', '" + newPassword + "', '" + newEmail + "');";
	char* errMsg = nullptr;

	// In cases where the user enters an epty string for any of the info, which should be considered invalid
	if (newUsername.empty() || newPassword.empty() || newEmail.empty()) { return; }

	int res = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errMsg);

	if(res != SQLITE_OK) {
		std::cerr << "Couldn't insert user info to the database" << std::endl << "New user was not created" << std::endl;
	}
}




bool SqliteDatabase::doesUserExist(std::string username) const {
	std::string selectQuery = "SELECT * FROM Users\nWHERE Username = '" + username + "';";
	char* errMsg = nullptr;
	SignupRequest userInfo { "", "", "" };

	if (username.empty()) { return false; }

	int res = sqlite3_exec(db, selectQuery.c_str(), userCallback, &userInfo, &errMsg);

	if (res != SQLITE_OK) {
		std::cerr << "Could not complete operation" << std::endl;
		return false;
	}

	return (userInfo.username == username);
}




bool SqliteDatabase::doesPasswordMatch(std::string username, std::string password) const {
	std::string selectQuery = "SELECT * FROM Users\nWHERE Username = '" + username + "';";
	char* errMsg = nullptr;
	SignupRequest userInfo{ "", "", "" };

	if (username.empty()) { return false; }

	int res = sqlite3_exec(db, selectQuery.c_str(), userCallback, &userInfo, &errMsg);

	if (res != SQLITE_OK) {
		std::cerr << "Could not complete operation" << std::endl;
		return false;
	}

	return (userInfo.password == password);
}




std::list<Question> SqliteDatabase::getQuestions(int numOfQuestions) const{
	int res = 0;
	char* errMsg = nullptr;
	// uses ORDER BY RANDOM() to get a random result for the answers every time, making the game more replayable
	std::string selectQuery = "SELECT * FROM Questions\nORDER BY RANDOM()\nLIMIT " + std::to_string(numOfQuestions) + ";";
	std::list<Question> questions;

	res = sqlite3_exec(db, selectQuery.c_str(), questionCallback, &questions, &errMsg);
	if (res != SQLITE_OK) {
		std::cerr << "Error could not select questions" << std::endl;
	}

	return questions;
}


float SqliteDatabase::getPlayerAverageAnswerTime(std::string username) const {
	int res = 0;
	char* errMsg = nullptr;
	std::string selectQuery = "SELECT AverageAnswerTime FROM Stats\nWHERE Username = '" + username + "';";
	std::pair<std::string, float> userStat;
	userStat.first = "AverageAnswerTime";

	res = sqlite3_exec(db, selectQuery.c_str(), statsCallback, &userStat, &errMsg);
	if (res != SQLITE_OK) {
		std::cerr << "Error could not select questions" << std::endl;
	}

	return userStat.second;
}


int SqliteDatabase::getNumOfCorrectAnswers(std::string username) const {
	int res = 0;
	char* errMsg = nullptr;
	std::string selectQuery = "SELECT CorrectAnswers FROM Stats\nWHERE Username = '" + username + "';";
	std::pair<std::string, float> userStat;
	userStat.first = "CorrectAnswers";

	res = sqlite3_exec(db, selectQuery.c_str(), statsCallback, &userStat, &errMsg);
	if (res != SQLITE_OK) {
		std::cerr << "Error could not select questions" << std::endl;
	}

	return ((int)userStat.second);
}


int SqliteDatabase::getNumOfTotalAnswers(std::string username) const {
	int res = 0;
	char* errMsg = nullptr;
	std::string selectQuery = "SELECT TotalAnswers FROM Stats\nWHERE Username = '" + username + "';";
	std::pair<std::string, float> userStat;
	userStat.first = "TotalAnswers";

	res = sqlite3_exec(db, selectQuery.c_str(), statsCallback, &userStat, &errMsg);
	if (res != SQLITE_OK) {
		std::cerr << "Error could not select questions" << std::endl;
	}

	return ((int)userStat.second);
}


int SqliteDatabase::getNumOfPlayerGames(std::string username) const {
	int res = 0;
	char* errMsg = nullptr;
	std::string selectQuery = "SELECT TotalGames FROM Stats\nWHERE Username = '" + username + "';";
	std::pair<std::string, float> userStat;
	userStat.first = "TotalGames";

	res = sqlite3_exec(db, selectQuery.c_str(), statsCallback, &userStat, &errMsg);
	if (res != SQLITE_OK) {
		std::cerr << "Error could not select questions" << std::endl;
	}

	return ((int)userStat.second);
}


std::vector<std::string> SqliteDatabase::getAllUsernames() const {
	int res = 0;
	char* errMsg = nullptr;
	std::string selectQuery = "SELECT Username FROM Users\nORDER BY Username ASC;";
	std::vector<std::string> names;

	res = sqlite3_exec(db, selectQuery.c_str(), nameCallback, &names, &errMsg);
	if (res != SQLITE_OK) {
		std::cerr << "Error could not select questions" << std::endl;
	}

	return names;
}




int userCallback(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "Username") {
			((SignupRequest*)data)->username = argv[i];
		}
		else if (std::string(azColName[i]) == "Password") {
			((SignupRequest*)data)->password = argv[i];
		}
		else if (std::string(azColName[i]) == "Email") {
			((SignupRequest*)data)->email = argv[i];
		}
	}

	return 0;
}




// Gets the question info, randomizes the answer order and puts it in the list
int questionCallback(void* data, int argc, char** argv, char** azColName) {
	Question curQuestion;
	std::string correctAns = "";
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "Question") {
			curQuestion.question = argv[i];
		}
		else if (std::string(azColName[i]) == "CorrectAnswer") {
			// saves correct answer to get it's index later
			correctAns = argv[i];
			curQuestion.answers.push_back(argv[i]);
		}
		else if (std::string(azColName[i]) == "Answer2" || std::string(azColName[i]) == "Answer3" || std::string(azColName[i]) == "Answer4") {
			curQuestion.answers.push_back(argv[i]);
		}
	}

	// randomizes the order of the answers to make the trivia game more replayable
	std::shuffle(curQuestion.answers.begin(), curQuestion.answers.end(), std::random_device());
	curQuestion.correctIndex = 0;

	for (uint8_t i = 0; i < curQuestion.answers.size(); i++) {
		curQuestion.correctIndex = (curQuestion.answers[i] == correctAns ? i : curQuestion.correctIndex);
	}

	((std::list<Question>*)data)->push_back(curQuestion);
	return 0;
}



int statsCallback(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == ((std::pair<std::string, float>*)data)->first) {
			((std::pair<std::string, float>*)data)->second = std::stof(std::string(argv[i]));
		}
	}
	return 0;
}



int nameCallback(void* data, int argc, char** argv, char** azColName) {
	std::string username = "";
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "Username") {
			username = argv[i];
		}
	}
	((std::vector<std::string>*)data)->push_back(username);
	return 0;
}




SqliteDatabase::~SqliteDatabase() {

	sqlite3_close(db);
	db = nullptr;

}