//---------------------------------------------------------------------------

#pragma hdrstop

#include "btrfcomm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


/*
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
						 Start of Android Bluetooth Class Function Declaration
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
*/



//Constructor for Android Bluetooth Class
DroidBT::DroidBT(void){



}
//---------------------------------------------------------------------------



//Checks whether the adapter is enabled/supported or not and returns a
//string with the answer
String DroidBT::CheckBluetooth(void){
	m_JBluetoothAdapter = TJBluetoothAdapter::JavaClass->getDefaultAdapter();
	String s = JStringToString(m_JBluetoothAdapter->getName());
	if (m_JBluetoothAdapter->isEnabled())
		return "Bluetooth for your " + s + " is enabled";
	else
		return "Bluetooth for your " + s + " is not enabled or not supported, please turn on bluetooth before you proceed";
}
//---------------------------------------------------------------------------



//Gets a list of paired/bonded devices from the adapter and returns the list
std::list<String> DroidBT::GetBonded(void){
	_di_JSet externalDevices;
	_di_JIterator it;
	std::list<String> result;


	m_JBluetoothAdapter = TJBluetoothAdapter::JavaClass->getDefaultAdapter();
	externalDevices = m_JBluetoothAdapter->getBondedDevices();

	//The following is to convert the JSet to a std::list
	it = externalDevices->iterator();

	while(it->hasNext()) {

		_di_ILocalObject i = _di_ILocalObject(it->next());
		m_JBluetoothDevice = TJBluetoothDevice::Wrap(i->GetObjectID());
		result.push_back(JStringToString(m_JBluetoothDevice->getName()) + "  || MAC=" + JStringToString(m_JBluetoothDevice->getAddress()));
	}

	return result;
}
//---------------------------------------------------------------------------


//Creates a thread that will attempt to connect to the given MAC address
void DroidBT::ConnectToDevice(String MAC){
    m_JBluetoothAdapter = TJBluetoothAdapter::JavaClass->getDefaultAdapter();
	m_JBluetoothDevice = m_JBluetoothAdapter->getRemoteDevice(StringToJString(MAC));
	m_JBluetoothSocket = m_JBluetoothDevice->createRfcommSocketToServiceRecord(MY_UUID);



	//Sets the connect flag to true, so that the thread will go through the connection path
		//This makes more sense why its necessary if you saw my unedited project code, you can delete this if you're safe and cautious with thread creation
	ConnectFlag = true;
	m_DroidBTConnectThread = new DroidBTConnectThread(this);




}
//---------------------------------------------------------------------------


//Closes the socket connection, and cancels device discovery
//Let user know if failed or successful
void DroidBT::CloseConnection(void){
	try {
		m_JBluetoothSocket->close();
		m_JBluetoothAdapter->cancelDiscovery();
		ShowMessage("Disconnected from Bluetooth");
	}
	catch (...) {
		ShowMessage("Unable to succesfully close Bluetooth Connection");
	}
}
//---------------------------------------------------------------------------

//Creates a thread that will continue to read from the module until either
//an exception occurs or the read switch is flipped off
void DroidBT::ReadFromDevice(bool FlagVal){
	ReadFlag = FlagVal;
	if(FlagVal == true)
		m_DroidBTRequestThread = new DroidBTRequestThread(this);
}
//---------------------------------------------------------------------------


//Creates a thread that will write to the module
void DroidBT::WriteToDevice(void){
	WriteFlag = true;
	m_DroidBTRequestThread = new DroidBTRequestThread(this);
}
//---------------------------------------------------------------------------



/*
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
						 End of Android Bluetooth Class Function Declaration
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
*/