#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string FileName = "FileClients.txt";
const string Delemeter = "====";


enum enMainMennueOptions {
	ShowClients = 1, AddNewClient, DeleteClient, UpdateClient,
	FindClient,TransActions, EndProgram
};

enum enTransactionsMenue {
	Deposit =1 ,Withdraw ,TotalBalances,MainMenue ,
};

struct sClient {

	string AccountNumber;
	string PinCode;
	string ClientName;
	string Phone;
	int Balance = 0;
	bool MarkForDelete = false;

};


vector<string> SplitLineToWordsInVector(string s);

string ConvertRecordToLine(sClient  Client);

sClient ConvertLineToRecord(string Line);

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

void EndProgrammScreen();

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



int main() {

	ShowMainMennue();

	return 0;
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
	cout << "\t\t[7] Exit " << endl;
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

	case EndProgram: {
		system("cls");
		EndProgrammScreen();
		GoBackToMainMenue();
	}
	}
}

void PerformTransactionsMenue(enTransactionsMenue TransactionsMenueOption) {

	vector<sClient> vClients = LoadClientsRecordFromFile(FileName);
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

	vector<sClient>vClients = LoadClientsRecordFromFile(FileName);

	sClient Client;

	cout << "\n\t----------------------------------------------------" << endl;
	cout << "\t\t+++ Balances Screen +++" << endl;
	cout << "\t----------------------------------------------------" << endl;

	ShowClientsBalances();
}

void ShowClientsBalances() {

	vector<sClient>vClients = LoadClientsRecordFromFile(FileName);

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

				SaveClientsToFile(FileName, vClients);

				cout << "\nDone Successfully . New Balance is : " << C.Balance << endl;
				cout << "\n";

				return 1;
			}
		}return 0;
}

void DepositScreen() {

	vector <sClient> vClients = LoadClientsRecordFromFile(FileName);

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

	vector <sClient>vClients = LoadClientsRecordFromFile(FileName);

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

string ConvertRecordToLine(sClient  Client) {

	string Record = "";

	Record += Client.AccountNumber + Delemeter;
	Record += Client.PinCode + Delemeter;
	Record += Client.ClientName + Delemeter;
	Record += Client.Phone + Delemeter;
	Record += to_string(Client.Balance);

	return Record;
}

sClient ConvertLineToRecord(string Line) {

	sClient Client;
	vector<string> vClientData = SplitLineToWordsInVector(Line);

		Client.AccountNumber = vClientData[0];
		Client.PinCode = vClientData[1];
		Client.ClientName = vClientData[2];
		Client.Phone = vClientData[3];
		Client.Balance = stoi(vClientData[4]);
	
	return Client;
}

void SaveClientsToFile(string FileName, vector<sClient>vClients) {

	fstream Myfile;
	Myfile.open(FileName, ios::out);

	string Line;

	for (sClient C : vClients) {
		if (C.MarkForDelete == false)
		{
			Line = ConvertRecordToLine(C);
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
		Client = ConvertLineToRecord(Line);

		vClients.push_back(Client);

	}Myfile.close();

	return vClients;
}

bool FindClientByAccountNumber(sClient& Client, string AccountNumber) {

	vector<sClient> vClients = LoadClientsRecordFromFile(FileName);

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

void ShowClientsListScreen() {

	vector<sClient>vClients = LoadClientsRecordFromFile(FileName);

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

	vector<sClient>vClients = LoadClientsRecordFromFile(FileName);

	sClient Client;
	char AddMoreClients;

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Add New Client Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	do {
		cout << "Adding New Client : " << endl;
		sClient Client = ReadNewClientData();
		string ClientRecordLine = ConvertRecordToLine(Client);

		fstream MyFile;
		MyFile.open(FileName, ios::out | ios::app);
		MyFile << ClientRecordLine << endl;
		MyFile.close();

		cout << "\nClient Added Successfully ,Do You Want To Add More Clients Y/N :";
		cin >> AddMoreClients;

	} while (toupper(AddMoreClients) == 'Y');

	vClients = LoadClientsRecordFromFile(FileName);

}

void MarkClientToDelete(string AccountNumber, vector<sClient>& vClients) {

	vClients = LoadClientsRecordFromFile(FileName);

	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
		}
	}
}

void DeleteClientScreen() {

	vector<sClient>vClients = LoadClientsRecordFromFile(FileName);

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

			SaveClientsToFile(FileName, vClients);
		}
		cout << "\nClient Deleted Successffuly" << endl;
	}
	else cout << "\nClient Not Found :(" << endl;

	vClients = LoadClientsRecordFromFile(FileName);
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

void UpdateClientScreen() {

	vector<sClient>vClients = LoadClientsRecordFromFile(FileName);

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

		}SaveClientsToFile(FileName, vClients);
		vClients = LoadClientsRecordFromFile(FileName);

	}
	else cout << "\nClient is Not Found \n";
}

void FindClientScreen() {

	vector<sClient>vClients = LoadClientsRecordFromFile(FileName);

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Find Client Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	vClients = LoadClientsRecordFromFile(FileName);

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

void EndProgrammScreen() {

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Programm End +++" << endl;
	cout << "----------------------------------------------------------" << endl;
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