#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string ClientsFile = "FileClients.txt";
const string UsersFile = "Users.txt";
const string Delemeter = "====";


enum enMainMennueOptions {
	ShowClients = 1, AddNewClient, DeleteClient, UpdateClient,
	FindClient,TransActions,ManageUsers, Log_out
};

enum enTransactionsMenue {
	Deposit =1 ,Withdraw ,TotalBalances,MainMenue ,
};

enum enManageUsersMennue {

	Users_List=1,Add_NewUser,Delete_User,Update_User,Find_User,MainMennue
};

enum enPermissions {
	pAll = -1, pClientList = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8,
	pFindClient = 16, pTrasActions = 32, pManageUsers = 64

};
struct sClient {

	string AccountNumber;
	string PinCode;
	string ClientName;
	string Phone;
	int Balance = 0;
	bool MarkForDelete = false;

};

struct sUserInfo {

	string UserName;
	string Password;
	short Permissions;
	bool MarkToDelete;
};

sUserInfo CurrentUser;

vector<string> SplitLineToWordsInVector(string s);

string ConvertRecordToLine_Client(sClient  Client);

sClient ConvertLineToRecord_Clients(string Line);

void SaveClientsToFile(string FileName, vector<sClient>vClients);

void PrintClientCard(sClient Client);

vector<sClient> LoadClientsRecordFromFile(string FileName);

bool FindClientByAccountNumber(sClient& Client, string AccountNumber);

void ShowOneClient(sClient Client);

void ShowClientsListScreen();

sClient ReadNewClientData();

void AddNewClientScreen();

void MarkClientToDelete(string AccountNumber, vector<sClient>& vClients);

void DeleteClientScreen();

sClient UpdateClientInfo(string AccountNumber);

void UpdateClientScreen();

void FindClientScreen();

void Logout();

string ReadAccountNumber();

enMainMennueOptions ReadOptionMainMenue();

enTransactionsMenue ReadOptionTracactionsMenue();

void GoBackToTransactionsMenue();

void DepositScreen();

void WithdrawScreen();

void ShowOneClientBalance(sClient Client);

void ShowClientsBalances();

void ShowBalancesScreen();

void PerformTransactionsMenue(enTransactionsMenue TransactionsMenueOption);

void ShowTransactionsMenue();

void PerformMainMenueOption(enMainMennueOptions MainMenueOption);

void ShowMainMennue();

void GoBackToMainMenue();

bool FindUserByUserNameAndPassword(string UserName,string Password ,sUserInfo &User);

void ShowManageUsersMennue();

void GoBackToManageUserMennue();

sUserInfo ReadNewUser();

int ReadPermissionsToSet();

void ShowAccessDeniedMessage();

void AddNewUserScreen();

void AddNewUser();

bool CheckPermissionsAccess(enPermissions Permission);

void UserListScreen();

void DeleteUser();

void FindUser();

bool LoadUserInfo(string UserName, string Password);

bool DepositBalanceToClientByAccountNumber(int DepositAmount, string AccountNumber, vector <sClient>& vClients);

bool UserExistByUserName(string UserName, string UserFile);

sUserInfo UpdateUserInfo(string UserName);

void UpdateUserScreen();

void MarkUserToDelete(string UserName, vector<sUserInfo>& vUsers);

void SaveUsersToFile(string UsersFile, vector<sUserInfo>vUsers);

string ConvertRecordToLine_Users(sUserInfo  User);

enManageUsersMennue ReadMnageUsersOption();

void PerformManageUserMennue(enManageUsersMennue ManageUsersMennueOption);

sUserInfo ConvertLineToRecord_Users(string Line);

vector<sUserInfo> LoadUsersRecordFromFile(string UsersFile);

void LoginScreen();

void Login();
//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------



int main() {

	Login();                           //-----------------------------------------------------------------
	                                  //-----------------------------------------------------------------
	return 0;
}


//----------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
void Login() {

	LoginScreen();
	
}

bool FindUserByUserNameAndPassword(string UserName,string Password,sUserInfo &User) {

	vector<sUserInfo> vUsers = LoadUsersRecordFromFile(UsersFile);

	for (sUserInfo & U : vUsers) {

		if (U.UserName == UserName && U.Password==Password)
		{
			User = U;
			return true;
		}
	}
	return false;
}

bool LoadUserInfo(string UserName, string Password) {

	if (FindUserByUserNameAndPassword(UserName,Password,CurrentUser))
		return 1;
	else
		return 0;
}

void LoginScreen() {

	bool LoginFailed = 0;
	string UserName, Password;

	do {
		system("cls");
		
		cout << "\n----------------------------------------------------------" << endl;
		cout << "\t\t+++ Login Screen +++" << endl;
		cout << "----------------------------------------------------------" << endl;

		if (LoginFailed)
		{
			cout << "Invalid UserName/Password !" << endl;
		}

		cout << "Enter User Name :";
		cin >> UserName;
		cout << "Enter Password :";
		cin >> Password;
		LoginFailed = !LoadUserInfo(UserName, Password);

	} while (LoginFailed);
	ShowMainMennue();
}

void GoBackToMainMenue() {

	system("pause");
	cout << "Press Any Key To Back To Main Menue ...";
	ShowMainMennue();

}

void ShowMainMennue() {

	system("cls");
	cout << "\n=========================================================" << endl;
	cout << "\t======== Main Mennue Screen ======== " << endl;
	cout << "=========================================================" << endl;
	cout << "\t\t[1] Show Client List " << endl;
	cout << "\t\t[2] Add New Client " << endl;
	cout << "\t\t[3] Delete Client " << endl;
	cout << "\t\t[4] Update Client Info " << endl;
	cout << "\t\t[5] Find Client " << endl;
	cout << "\t\t[6] Transactions Menue Screen " << endl;
	cout << "\t\t[7] Manage Users " << endl;
	cout << "\t\t[8] LogOut " << endl;
	cout << "=========================================================" << endl;
	PerformMainMenueOption(ReadOptionMainMenue());
}

void PerformMainMenueOption(enMainMennueOptions MainMenueOption) {

	switch (MainMenueOption)
	{
	case ShowClients: {
		system("cls");
		ShowClientsListScreen();
		GoBackToMainMenue();
	}
					break;

	case AddNewClient: {
		system("cls");
		AddNewClientScreen();
		GoBackToMainMenue();
	}
					 break;

	case DeleteClient: {
		system("cls");
		DeleteClientScreen();
		GoBackToMainMenue();
	}
					 break;

	case UpdateClient: {
		system("cls");
		UpdateClientScreen();
		GoBackToMainMenue();
	}
					 break;

	case FindClient: {
		system("cls");
		FindClientScreen();
		GoBackToMainMenue();
	}
				   break;

	
	case TransActions: {
		system("cls");
		ShowTransactionsMenue();
		GoBackToMainMenue();
	}
					 break;

	case ManageUsers: {
		system("cls");
		ShowManageUsersMennue();
		GoBackToMainMenue();
	}
					 break;

	case Log_out: {
		system("cls");
		Logout();
		GoBackToMainMenue();
	}
	}
}

void ShowManageUsersMennue() {

	if (!CheckPermissionsAccess(pManageUsers))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n=========================================================" << endl;
	cout << "\t======== Manage Users Screen ======== " << endl;
	cout << "=========================================================" << endl;
	cout << "\t\t[1] List Users  \n" ;
	cout << "\t\t[2] Add New User \n";
	cout << "\t\t[3] Delete User  \n";
	cout << "\t\t[4] Update User  \n";
	cout << "\t\t[5] Find User  \n";
	cout << "\t\t[6] Main Mennue  \n";
	cout << "=========================================================" << endl;
	PerformManageUserMennue(ReadMnageUsersOption());
}

enManageUsersMennue ReadMnageUsersOption() {
	short Option;
	cout << "choose What Do You Want To Do ? [1 - 6] ";
	cin >> Option;
	return (enManageUsersMennue)Option;
}

void PerformManageUserMennue(enManageUsersMennue ManageUsersMennueOption) {

	vector<sUserInfo> vUsersInfo = LoadUsersRecordFromFile(UsersFile);
	switch (ManageUsersMennueOption) {
	case Users_List:
	{
		system("cls");
		UserListScreen();
		GoBackToManageUserMennue();

		break;
	}
	case Add_NewUser:
	{
		system("cls");
		AddNewUserScreen();
		GoBackToManageUserMennue();

		break;
	}
	case Delete_User:
	{
		system("cls");
		DeleteUser();
		GoBackToManageUserMennue();
		break;
	}
	case Update_User:
	{
		system("cls");
		UpdateUserScreen();
		GoBackToManageUserMennue();
		break;
	}
	case Find_User:
	{
		system("cls");
		FindUser();
		GoBackToManageUserMennue();
		break;
	}


	}
}

void FindUser() {

cout << "\n----------------------------------------------------------" << endl;
cout << "\t\t+++ Delete Users Screen +++" << endl;
cout << "----------------------------------------------------------" << endl;


	vector<sUserInfo>vUsers = LoadUsersRecordFromFile(UsersFile);
	string UserName;
	cout << "\nEnter User Name :";
	cin >> UserName;
	if (UserExistByUserName(UserName,UsersFile))
	{
		cout << "\nUser Found :)" << endl;
	}
	else cout << "Not Found :(" << endl;
}

void DeleteUser() {

	vector<sUserInfo>vUsers = LoadUsersRecordFromFile(UsersFile);

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Delete Users Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	string UserName;
	sUserInfo User;
	char DeleteUser = 'n';

	cout << "Enter User Name :";
	cin >> UserName;
	cout << "\n";
	if (UserExistByUserName(UserName,UsersFile))
	{
		cout << "\nUser Found , Are You Sure Do You Want To Delete This Users Y/N :";
		cin >> DeleteUser;
		cout << "\n";
		if (toupper(DeleteUser) == 'Y')
		{
			MarkUserToDelete(UserName, vUsers);

			SaveUsersToFile(UsersFile, vUsers);
		}
		cout << "\nUser Deleted Successffuly" << endl;
	}
	else cout << "\nUser Not Found :(" << endl;

	vUsers = LoadUsersRecordFromFile(UsersFile);
}

void AddNewUser() {

	vector<sUserInfo> vUsers = LoadUsersRecordFromFile(UsersFile);

	char AddMoreUsers = ' ';

	do {
		cout << "Adding New User : " << endl;
		sUserInfo User = ReadNewUser();
		string UserRecordLine = ConvertRecordToLine_Users(User);

		fstream MyFile;
		MyFile.open(UsersFile, ios::out | ios::app);
		MyFile << UserRecordLine << endl;
		MyFile.close();

		cout << "\nUser Added Successfully ,Do You Want To Add More Clients Y/N :";
		cin >> AddMoreUsers;

	} while (toupper(AddMoreUsers) == 'Y');

	vUsers = LoadUsersRecordFromFile(UsersFile);
}

void AddNewUserScreen() {

	vector<sUserInfo> vUsers = LoadUsersRecordFromFile(UsersFile);

	sUserInfo User;
	char AddMoreUsers;

	cout << "\n\t----------------------------------------------------" << endl;
	cout << "\t\t+++ Add New User Screen +++" << endl;
	cout << "\t----------------------------------------------------" << endl;

	AddNewUser();
}

bool UserExistByUserName(string UserName, string UsersFile) {

	vector<sUserInfo> vUsers = LoadUsersRecordFromFile(UsersFile);

	for (sUserInfo& U : vUsers) {

		if (U.UserName == UserName)
			return 1;
	}return 0;
}

int ReadPermissionsToSet() {
	int Permissions = 0;
	char Answer = ' ';

	cout << "Do You Want To Give All Permissions y/n : ";
	cin >> Answer;
	if (tolower(Answer) == 'y')
	{
		return -1;
	}

	cout << "Do You Want To Give Access To :\n";

	cout << "Show Client List y/n :";
	cin >> Answer;
	if (tolower(Answer) == 'y')
	{
		Permissions += pClientList;
	}
	cout << "Add New Client y/n :";
	cin >> Answer;
	if (tolower(Answer) == 'y')
	{
		Permissions += pAddNewClient;
	}
	cout << "Delete Client y/n :";
	cin >> Answer;
	if (tolower(Answer) == 'y')
	{
		Permissions += pDeleteClient;
	}
	cout << "Update Client y/n :";
	cin >> Answer;
	if (tolower(Answer) == 'y')
	{
		Permissions += pUpdateClient;
	}
	cout << "Find Client y/n :";
	cin >> Answer;
	if (tolower(Answer) == 'y')
	{
		Permissions += pFindClient;
	}
	cout << "Transactions y/n :";
	cin >> Answer;
	if (tolower(Answer) == 'y')
	{
		Permissions += pTrasActions;
	}
	cout << "Manage Users y/n :";
	cin >> Answer;
	if (tolower(Answer) == 'y')
	{
		Permissions += pManageUsers;
	}

	return Permissions;

}

sUserInfo ReadNewUser() {

	sUserInfo User;

	do {
		cout << "Enter UserName :";
		getline(cin >> ws, User.UserName);
		if (!UserExistByUserName(User.UserName,UsersFile))
		{
			cout << "Enter Password :";
			cin >> User.Password;
		}
		else cout << "User Found .. Enter Another user " << endl;

	} while (UserExistByUserName(User.UserName,UsersFile));

	cout << "Enter Permissions : ";

	User.Permissions = ReadPermissionsToSet();

	return User;
}

void GoBackToManageUserMennue() {

	system("pause");
	cout << "Press Any Key To Back To Manage Users Menue ...";
	system("cls");
	ShowManageUsersMennue();

}

void UserListScreen() {


	vector<sUserInfo> vUsers = LoadUsersRecordFromFile(UsersFile);

	cout << "\n\t----------------------------------------------------" << endl;
	cout << "\t\t\t+++ User List Screen +++" << endl;
	cout << "\t----------------------------------------------------" << endl;
	
	cout << "---------------------------------------------------------------" << endl;
	cout << setw(20) << left << "UserName" << "|" << setw(20) << left << "Password" << "|" << setw(20) << left << "Permission" << "|" << endl;
	cout << "--------------------------------------------------------------- " << endl;

	for (sUserInfo& U : vUsers) {

		cout << setw(20) << left << U.UserName << "|" << setw(20) << left << U.Password
			<< "|" << setw(20) << left << U.Permissions << "|" << endl;
	
	}
	cout << "---------------------------------------------------------------" << endl;
}

void PerformTransactionsMenue(enTransactionsMenue TransactionsMenueOption) {

	vector<sClient> vClients = LoadClientsRecordFromFile(ClientsFile);
	switch (TransactionsMenueOption) {

	case Deposit:
	{
		system("cls");
		DepositScreen();
		GoBackToTransactionsMenue();
	}
	break;
	case Withdraw:
	{
		system("cls");
		WithdrawScreen();
		GoBackToTransactionsMenue();
	}
	break;
	case TotalBalances:
	{
		system("cls");
		ShowBalancesScreen();
		GoBackToTransactionsMenue();

	}
	case MainMenue:
		system("cls");
		ShowMainMennue();
		GoBackToTransactionsMenue();
	}
}

void ShowTransactionsMenue() {

	if (!CheckPermissionsAccess(pTrasActions))
	{
		ShowAccessDeniedMessage();
		return;
	}


	cout << "\n=========================================================" << endl;
	cout << "\t======== Transactions Menue Screen ======== " << endl;
	cout << "=========================================================" << endl;
	cout << "\t\t[1] Deposit  " << endl;
	cout << "\t\t[2] Withdraw " << endl;
	cout << "\t\t[3] Total Balance " << endl;
	cout << "\t\t[4] Main Menue " << endl;
	cout << "=========================================================" << endl;

	PerformTransactionsMenue(ReadOptionTracactionsMenue());
}

void GoBackToTransactionsMenue() {

	system("pause");
	cout << "Press to any key to go to transactions menue ...";
	system("cls");
	ShowTransactionsMenue();
}

void ShowBalancesScreen() {

	vector<sClient>vClients = LoadClientsRecordFromFile(ClientsFile);

	sClient Client;

	cout << "\n\t----------------------------------------------------" << endl;
	cout << "\t\t+++ Balances Screen +++" << endl;
	cout << "\t----------------------------------------------------" << endl;

	ShowClientsBalances();
}

void ShowClientsBalances() {

	vector<sClient>vClients = LoadClientsRecordFromFile(ClientsFile);

	cout << "\t\tBalances List ( " << vClients.size() << " ) Clients(s)" << endl;

	cout << "___________________________________________________________________________\n\n";
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Balance" << " |";
	cout << "\n___________________________________________________________________________\n";

	int TotalBalances = 0;

	for (sClient& C : vClients) {
		ShowOneClientBalance(C);
		TotalBalances += C.Balance;
		cout << "\n";
	}
	cout << "___________________________________________________________________________\n\n";

	cout << "\t\t\tTotal Balances : " << TotalBalances << endl;
	cout << "\n\n";

}

string ReadAccountNumber() {

	string AccountNumber;

	cout << "Enter Account Number :";
	cin >> AccountNumber;
	cout << "\n";
	return AccountNumber;

}

bool DepositBalanceToClientByAccountNumber(int DepositAmount,string AccountNumber,vector <sClient>& vClients) {

	char answer = 'n';

	cout << "Are You Sure Do You Want To Perform This Transactions  y/n : ";
	cin >> answer;

	if (tolower(answer) == 'y')

		for (sClient &C : vClients) {

			if (C.AccountNumber == AccountNumber)
			{
				C.Balance += DepositAmount;

				SaveClientsToFile(ClientsFile, vClients);

				cout << "\nDone Successfully . New Balance is : " << C.Balance << endl;
				cout << "\n";

				return 1;
			}
		}return 0;
}

void DepositScreen() {

	vector <sClient> vClients = LoadClientsRecordFromFile(ClientsFile);

	sClient Client;

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Deposit Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	string AccountNumber;
	do {
		AccountNumber = ReadAccountNumber();

		if (!FindClientByAccountNumber(Client, AccountNumber))
		{
			cout << "Client with " << AccountNumber << " Does not exist \n" << endl;

		}
	} while (!FindClientByAccountNumber(Client, AccountNumber));

	cout << "The Following Are Client Details :" << endl;
	PrintClientCard(Client);

	int DepositAmount = 0;

	cout << "Please Enter Deposit Amount :";
	cin >> DepositAmount;

	DepositBalanceToClientByAccountNumber(DepositAmount, AccountNumber, vClients);
}

void WithdrawScreen() {

	vector <sClient>vClients = LoadClientsRecordFromFile(ClientsFile);

	sClient Client;

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Withdraw Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	string AccountNumber;
	do {
		AccountNumber = ReadAccountNumber();

		if (!FindClientByAccountNumber(Client, AccountNumber))
		{
			cout << "Client with " << AccountNumber << " Does not exist " << endl;

		}
	} while (!FindClientByAccountNumber(Client, AccountNumber));

	cout << "The Following Are Client Details :" << endl;
	PrintClientCard(Client);

	int WithdrawAmount;

	cout << "Enter Amount :";
	cin >> WithdrawAmount;

	while (WithdrawAmount > Client.Balance) {

		cout << "\nAmount exceeds The Balance " << endl;
		cout << "Enter amount Less or Equal The Balance " << endl;
		cin >> WithdrawAmount;
	}

	DepositBalanceToClientByAccountNumber(WithdrawAmount * -1, AccountNumber, vClients);
}

void ShowOneClientBalance(sClient Client) {

	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.ClientName;
	cout << "| " << setw(12) << left << Client.Balance << " |";
}

vector<string> SplitLineToWordsInVector(string s)
{

	vector<string> vString;

	short position = 0;
	string word;

	while ((position = s.find(Delemeter)) != std::string::npos) {

		word = s.substr(0, position);

		if (!word.empty()) {

			vString.push_back(word);

		}s.erase(0, position + Delemeter.length());

	}if (!s.empty())
		vString.push_back(s);

	return vString;
}

string ConvertRecordToLine_Client(sClient  Client) {

	string Record = "";

	Record += Client.AccountNumber + Delemeter;
	Record += Client.PinCode + Delemeter;
	Record += Client.ClientName + Delemeter;
	Record += Client.Phone + Delemeter;
	Record += to_string(Client.Balance);

	return Record;
}

string ConvertRecordToLine_Users(sUserInfo  User) {

	string Record = "";

	Record += User.UserName + Delemeter;
	Record += User.Password + Delemeter;
	Record += to_string(User.Permissions);

	return Record;
}

sClient ConvertLineToRecord_Clients(string Line) {

	sClient Client;
	vector<string> vClientData = SplitLineToWordsInVector(Line);

		Client.AccountNumber = vClientData[0];
		Client.PinCode = vClientData[1];
		Client.ClientName = vClientData[2];
		Client.Phone = vClientData[3];
		Client.Balance = stoi(vClientData[4]);
	
	return Client;
}

sUserInfo ConvertLineToRecord_Users(string Line) {

	sUserInfo User;
	vector<string> vUsers = SplitLineToWordsInVector(Line);

	User.UserName = vUsers[0];
	User.Password = vUsers[1];
	User.Permissions = stoi(vUsers[2]);

	return User;
}

void SaveClientsToFile(string FileName, vector<sClient>vClients) {

	fstream Myfile;
	Myfile.open(FileName, ios::out);

	string Line;

	for (sClient C : vClients) {
		if (C.MarkForDelete == false)
		{
			Line = ConvertRecordToLine_Client(C);
			Myfile << Line << endl;
		}

	}Myfile.close();
}

void SaveUsersToFile(string UsersFile, vector<sUserInfo>vUsers) {

	fstream Myfile;
	Myfile.open(UsersFile, ios::out);

	string Line;

	for (sUserInfo & U : vUsers) {
		if(U.MarkToDelete==false)
		{
			Line = ConvertRecordToLine_Users(U);
			Myfile << Line << endl;
		}

	}Myfile.close();
}

void PrintClientCard(sClient Client) {

	cout << "----------------------------------------------------------" << endl;
	cout << "Account Number :" << Client.AccountNumber << endl;
	cout << "Pin Code       :" << Client.PinCode << endl;
	cout << "Client Name    :" << Client.ClientName << endl;
	cout << "Phone          :" << Client.Phone << endl;
	cout << "Balance        :" << Client.Balance << endl;
	cout << "----------------------------------------------------------" << endl;
}

vector<sClient> LoadClientsRecordFromFile(string FileName) {

	vector<sClient> vClients;

	fstream Myfile;

	Myfile.open(FileName, ios::in);
	sClient Client;
	string Line;

	while (getline(Myfile, Line)) {
		if (Line == "" || Line == "\n")
			continue;
		Client = ConvertLineToRecord_Clients(Line);

		vClients.push_back(Client);

	}Myfile.close();

	return vClients;
}

vector<sUserInfo> LoadUsersRecordFromFile(string FileUsers) {

	vector<sUserInfo> vUsers;

	fstream Myfile;

	Myfile.open(FileUsers, ios::in);
	sUserInfo User;
	string Line;

	while (getline(Myfile, Line)) {
		if (Line == "" || Line == "\n")
			continue;
		User = ConvertLineToRecord_Users(Line);

		vUsers.push_back(User);

	}Myfile.close();

	return vUsers;
}

bool FindClientByAccountNumber(sClient& Client, string AccountNumber) {

	vector<sClient> vClients = LoadClientsRecordFromFile(ClientsFile);

	for (sClient& C : vClients) {

		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

void ShowOneClient(sClient Client) {

	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.ClientName;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.Balance << " |";
	cout << "\n";
	cout << "_____________________________________________________________________________________________________";


}

bool CheckPermissionsAccess(enPermissions Permission) {
	if (CurrentUser.Permissions == pAll)
		return true;
	if ((Permission & CurrentUser.Permissions) == Permission)
		return true;
	else 
		return 0;

}

void ShowAccessDeniedMessage() {

	cout << "\nAccess Denied, \nYou Don't Have Access To Do This Operation  .. \nPlease Contact Admin :)" << endl;
}

void ShowClientsListScreen() {

	if (!CheckPermissionsAccess(pClientList))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
		return;
	}
	vector<sClient>vClients = LoadClientsRecordFromFile(ClientsFile);

	cout << "\n\t\t\t\t_____________________________" << endl;
	cout << "\t\t\t\tClients List ( " << vClients.size() << " ) Clients(s)" << endl;

	cout << "_____________________________________________________________________________________________________\n\n";
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(10) << left << "Pin Code";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Balance" << " |";
	cout << "\n_____________________________________________________________________________________________________\n";

	for (sClient& C : vClients) {
		ShowOneClient(C);
		cout << "\n";
	}

	cout << "\n\n";
}

sClient ReadNewClientData() {
	sClient Client;

	cout << "Enter Client Account Number :";
	getline(cin >> ws, Client.AccountNumber);

	while (FindClientByAccountNumber(Client, Client.AccountNumber)) {
		cout << "\nAccount Number already exists! Enter another one: ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter Pin Code :";
	getline(cin, Client.PinCode);

	cout << "Enter Client Name :";
	getline(cin, Client.ClientName);

	cout << "Enter Phone :";
	getline(cin, Client.Phone);

	cout << "Enter Balance :";
	cin >> Client.Balance;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // IMPORTANT FIX

	return Client;
}

void AddNewClientScreen() {

	if (!CheckPermissionsAccess(pAddNewClient))
		ShowAccessDeniedMessage();

	vector<sClient>vClients = LoadClientsRecordFromFile(ClientsFile);

	sClient Client;
	char AddMoreClients;

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Add New Client Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	do {
		cout << "Adding New Client : " << endl;
		sClient Client = ReadNewClientData();
		string ClientRecordLine = ConvertRecordToLine_Client(Client);

		fstream MyFile;
		MyFile.open(ClientsFile, ios::out | ios::app);
		MyFile << ClientRecordLine << endl;
		MyFile.close();

		cout << "\nClient Added Successfully ,Do You Want To Add More Clients Y/N :";
		cin >> AddMoreClients;

	} while (toupper(AddMoreClients) == 'Y');

	vClients = LoadClientsRecordFromFile(ClientsFile);

}

void MarkClientToDelete(string AccountNumber, vector<sClient>& vClients) {

	vClients = LoadClientsRecordFromFile(ClientsFile);

	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
		}
	}
}

void MarkUserToDelete(string UserName, vector<sUserInfo>& vUsers) {

	vUsers = LoadUsersRecordFromFile(UsersFile);

	for (sUserInfo& C : vUsers)
	{
		if (C.UserName == UserName)
		{
			C.MarkToDelete = true;
		}
	}
}

void DeleteClientScreen() {

	if (!CheckPermissionsAccess(pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector<sClient>vClients = LoadClientsRecordFromFile(ClientsFile);

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Delete Client Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	string AccountNumber;
	sClient Client;
	char DeleteClient;

	AccountNumber = ReadAccountNumber();

	cout << "\n";
	if (FindClientByAccountNumber(Client, AccountNumber))
	{
		PrintClientCard(Client);
		cout << "\nClient Found , Are You Sure Do You Want To Delete This Client Y/N :";
		cin >> DeleteClient;
		cout << "\n";
		if (toupper(DeleteClient) == 'Y')
		{
			MarkClientToDelete(AccountNumber, vClients);

			SaveClientsToFile(ClientsFile, vClients);
		}
		cout << "\nClient Deleted Successffuly" << endl;
	}
	else cout << "\nClient Not Found :(" << endl;

	vClients = LoadClientsRecordFromFile(ClientsFile);
}

sClient UpdateClientInfo(string AccountNumber) {

	sClient Client;

	Client.AccountNumber = AccountNumber;
	cout << "\nEnter New Pin Code :";
	getline(cin, Client.PinCode);
	cout << "\nEnter New Client Name :";
	getline(cin,Client.ClientName);
	cout << "\nEnter New Phone :";
	cin >> Client.Phone;
	cout << "\nEnter New Balance :";
	cin >> Client.Balance;

	return Client;
}

sUserInfo UpdateUserInfo(string UserName) {

	sUserInfo User;

	User.UserName = UserName;
	cout << "\nEnter New Password :";
	getline(cin, User.Password);
	cout << "\nEnter New Permissions :";
	User.Permissions = ReadPermissionsToSet();

	return User;
}

void UpdateClientScreen() {

	if (!CheckPermissionsAccess(pUpdateClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector<sClient>vClients = LoadClientsRecordFromFile(ClientsFile);

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Update Client Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	string AccountNumber;
	sClient Client;
	char Update;
	
	 AccountNumber= ReadAccountNumber();

	if (FindClientByAccountNumber(Client, AccountNumber))
	{
		cout << "\nThe Following Are Client Details :\n";
		PrintClientCard(Client);

		cout << "\nAre You Sure Do You Want To Update This Client Y/N :";
		cin >> Update;
		cout << "\n";
		if (toupper(Update) == 'Y')
		{
			for (sClient& C : vClients) {

				if (C.AccountNumber == AccountNumber)

					C = UpdateClientInfo(AccountNumber);
				break;
			}
			cout << "_______________________________\n";
			cout << "\nClient Updated Successfully \n";

		}SaveClientsToFile(ClientsFile, vClients);
		vClients = LoadClientsRecordFromFile(ClientsFile);

	}
	else cout << "\nClient is Not Found \n";
}

void UpdateUserScreen() {

	vector<sUserInfo>vUsers = LoadUsersRecordFromFile(UsersFile);

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Update Users Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	string UserName;
	sClient User;
	char Update;

	cout << "Enter User Name That You Want To Update :";
	cin >> UserName;


	if (UserExistByUserName(UserName,UsersFile))
	{
		cout << "User Found " << endl;
		cout << "\nAre You Sure Do You Want To Update This User Y/N :";
		cin >> Update;
		cout << "\n";
		if (toupper(Update) == 'Y')
		{
			for (sUserInfo& U : vUsers) {

				if (U.UserName == UserName)

					U = UpdateUserInfo(UserName);
				break;
			}
			cout << "_______________________________\n";
			cout << "\nUser Updated Successfully \n";

		}SaveUsersToFile(UsersFile, vUsers);
		vUsers = LoadUsersRecordFromFile(ClientsFile);

	}
	else cout << "\nUser is Not Found \n";
}

void FindClientScreen() {

	if (!CheckPermissionsAccess(pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector<sClient>vClients = LoadClientsRecordFromFile(ClientsFile);

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Find Client Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	vClients = LoadClientsRecordFromFile(ClientsFile);

	sClient Client;
	string AccountNumber;
	AccountNumber = ReadAccountNumber();
	cout << "\n";
	if (FindClientByAccountNumber(Client, AccountNumber))
	{
		cout << "\nClient Found ,These Are His Details :\n";
		PrintClientCard(Client);
	}
	else cout << "\nClient Not Found" << endl;
}

void Logout() {
	Login();
}

enMainMennueOptions ReadOptionMainMenue() {
	short option;
	cout << "\nChoose what Do You Want To Do ! [1 to 6] :";
	cin >> option;
	cout << "\n";
	return (enMainMennueOptions)option;
}

enTransactionsMenue ReadOptionTracactionsMenue() {

	short option;
	cout << "\nChoose what Do You Want To Do ! [1 to 4] :";
	cin >> option;
	cout << "\n";
	return (enTransactionsMenue)option;
}