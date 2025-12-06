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
	FindClient, EndProgram
};

struct sClient {

	string AccountNumber;
	string PinCode;
	string ClientName;
	string Phone;
	string Balance;
	bool MarkForDelete = false;

};


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

	}if (s != "")
		vString.push_back(s);

	return vString;
}

string ConvertRecordToLine(sClient  Client) {

	string Record = "";

	Record += Client.AccountNumber + Delemeter;
	Record += Client.PinCode + Delemeter;
	Record += Client.ClientName + Delemeter;
	Record += Client.Phone + Delemeter;
	Record += Client.Balance;

	return Record;
}

sClient ConvertLineToRecord(string Line) {

	sClient Client;
	vector<string> vClientData = SplitLineToWordsInVector(Line);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.ClientName = vClientData[2];
	Client.Phone = vClientData[3];
	Client.Balance = vClientData[4];

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

	cout << "\n----------------------------------------------------------" << endl;
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
}

void ShowClientsListScreen(vector<sClient>vClients) {
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
	cout << "_____________________________________________________________________________________________________\n\n";

	cout << "\n\n";
}

sClient ReadNewClientData() {
	sClient Client;

	cout << "Enter Client Account Number :";
	cin >> Client.AccountNumber;

	if (FindClientByAccountNumber(Client, Client.AccountNumber))
	{
		PrintClientCard(Client);

		cout << "\nClient With Account Number (" << Client.AccountNumber <<
			")Already Exist , Enter Another Account Number ! :";
		cin >> Client.AccountNumber;

		cout << "\n";
	}
	cout << "Enter Pin Code :";
	cin >> Client.PinCode;
	cout << "Enter Client Name :";
	cin >> Client.ClientName;
	cout << "Enter Phone :";
	cin >> Client.Phone;
	cout << "Enter Balance :";
	cin >> Client.Balance;

	return Client;
}

void AddNewClientScreen(vector<sClient>& vClients) {

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

void DeleteClientScreen(vector<sClient> vClients) {

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Delete Client Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	string AccountNumber;
	sClient Client;
	char DeleteClient;

	cout << "\nEnter Account Number Of Client That You Want To Delete :";
	cin >> AccountNumber;
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
	cin >> Client.PinCode;
	cout << "\nEnter New Client Name :";
	cin >> Client.ClientName;
	cout << "\nEnter New Phone :";
	cin >> Client.Phone;
	cout << "\nEnter New Balance :";
	cin >> Client.Balance;

	return Client;
}

void UpdateClientScreen(vector<sClient>vClients) {

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Update Client Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	string AccountNumber;
	sClient Client;
	char Update;
	cout << "\nEnter Client Number That You Want To Update :";
	cin >> AccountNumber;

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

void FindClientScreen(vector<sClient>vClients) {

	cout << "\n----------------------------------------------------------" << endl;
	cout << "\t\t+++ Find Client Screen +++" << endl;
	cout << "----------------------------------------------------------" << endl;

	vClients = LoadClientsRecordFromFile(FileName);

	sClient Client;
	string AccountNumber;
	cout << "\nEnter Account Number Of Client That You Looking For :";
	cin >> AccountNumber;
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

enMainMennueOptions ReadOption() {
	short option;
	cout << "\nChoose what Do You Want To Do ! [1 to 6] :";
	cin >> option;
	cout << "\n";
	return (enMainMennueOptions)option;
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
	cout << "\t\t[6] Exit " << endl;
	cout << "=========================================================" << endl;
}

void StartProgram() {

	vector<sClient>vClients = LoadClientsRecordFromFile(FileName);
	do {
		ShowMainMennue();
		enMainMennueOptions Option = ReadOption();
		system("cls");
		switch (Option)
		{
		case ShowClients: ShowClientsListScreen(vClients);
			break;
		case AddNewClient:AddNewClientScreen(vClients);
			break;
		case DeleteClient:DeleteClientScreen(vClients);
			break;
		case UpdateClient:UpdateClientScreen(vClients);
			break;
		case FindClient:FindClientScreen(vClients);
			break;
		case EndProgram:EndProgrammScreen();

		}
		system("pause");
	} while (true);
}

int main() {
	StartProgram();
	cout << "Hello world " << endl;
	return 0;
}
