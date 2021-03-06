//---------------------------------------------------------------------------

#include <fmx.h>


#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;



TBluetoothDevice * BtDevice = NULL;
TBluetoothSocket * BtSocket = NULL;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
	//if(Bluetooth1->CurrentAdapter == NULL)
	  //	return;
	try{
	Bluetooth1->Enabled = true;
	TBluetoothDeviceList * mypaired = Bluetooth1->PairedDevices();
	String output = "";

	for (int i = 0; i < mypaired->Count; i++) {
		PairedDevicesList->Items->Add(mypaired->Items[i]->DeviceName);
		//output += mypaired->Items[i]->DeviceName + ": "+ mypaired->Items[i]->Address + "\n";
	}
	}catch(...){
    }
	//ShowMessage(output);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ConnectBtnClick(TObject *Sender)
{
	//if(Bluetooth1->CurrentAdapter == NULL)
	  //	return;

	if(BtSocket != NULL)
		if(BtSocket->Connected){
			BtSocket->Close();
			LogMemo->Lines->Add("Connection closed.");
			ConnectBtn->Text = "Connect";
			delete BtSocket;
            BtSocket = NULL;
            return;
		}


	TBluetoothDeviceList * mypaired = Bluetooth1->PairedDevices();
	int PairedDeviceNr = PairedDevicesList->ItemIndex;

	BtDevice = mypaired->Items[PairedDeviceNr];
	TBluetoothServiceList * myServices = Bluetooth1->GetServices(mypaired->Items[PairedDeviceNr]);
	 String help = "Services of Bluetooth Device """ + BtDevice->DeviceName + """: \n \n";

	for(int i=0;i<myServices->Count;i++){
	   help += myServices->Items[i].Name + ": " + GUIDToString(myServices->Items[i].UUID) + "\n";
	}

	LogMemo->Lines->Add(help);

	LogMemo->Lines->Add("Establishing connection...");

	//UUID for serial port: {00001101-0000-1000-8000-00805F9B34FB}
	GUID SerialUUID = StringToGUID("{00001101-0000-1000-8000-00805F9B34FB}");
	BtSocket = Bluetooth1->CreateClientSocket(BtDevice,SerialUUID,false);
	try{
		BtSocket->Connect();
	}
	catch(Exception& e){

		LogMemo->Lines->Add("Error. Not Connected. "+e.Message);
		return;
	}
	LogMemo->Lines->Add("Successfully connected.");
	ConnectBtn->Text = "Disconnect";

}



String BaToStr(TBytes bytes){
	String out = "";
	for(int i=0;i<bytes.Length;i++){
		out += bytes[i];
	}
	return out;
}



//---------------------------------------------------------------------------
void __fastcall TForm1::SendBtnClick(TObject *Sender)
{

if(BtSocket != NULL)
	if(BtSocket->Connected){
		//TBytes * myArray = new TBytes((AnsiString(CommandEdit->Text).c_str()));
		TBytes myArray;

		myArray.set_length(CommandEdit->Text.Length());
		for(int i = 0; i<CommandEdit->Text.Length();i++){
			myArray[i] = (unsigned char)(AnsiString(CommandEdit->Text)).c_str()[i];
		}

		BtSocket->SendData(myArray);
        LogMemo->Lines->Add("Sent: " + CommandEdit->Text);
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
if(BtSocket != NULL) {
	if(BtSocket->Connected){
		TBytes received;
		received = BtSocket->ReceiveData(90);
		if(received.Length > 0)
			LogMemo->Lines->Add("Received: "+ BaToStr(received));
		Label2->Text = "Online";
	}else
        Label2->Text = "Offline, but Socket exists??";
}
else
	Label2->Text = "Offline";

}
//---------------------------------------------------------------------------


