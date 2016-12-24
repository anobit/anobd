//---------------------------------------------------------------------------

#ifndef btrfcommH
#define btrfcommH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Androidapi.JNI.Bluetooth.hpp>
#include <Androidapi.Helpers.hpp>

#include <list>

#include "btthread.h"

//---------------------------------------------------------------------------

    //Forward declaration for use in thread declaration

/*
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
						 Start of Android Bluetooth Class Declaration
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
*/

//Class containing Android Bluetooth functions
class DroidBT {

	public:

	//Bluetooth objects
	_di_JBluetoothAdapter m_JBluetoothAdapter;
	_di_JBluetoothDevice m_JBluetoothDevice;
	_di_JBluetoothSocket m_JBluetoothSocket;
	_di_JInputStream m_JInputStream;
    _di_JOutputStream m_JOutputStream;

	//UUID of SPP/RFCOMM devices
	_di_JUUID MY_UUID = TJUUID::JavaClass->fromString(StringToJString("00001101-0000-1000-8000-00805F9B34FB"));


	//Threads
	DroidBTConnectThread *m_DroidBTConnectThread;
	DroidBTRequestThread *m_DroidBTRequestThread;
	DroidBTResponseThread *m_DroidBTResponseThread;



	unsigned char Response[32] = {0};


	//Connection flags
	bool ConnectFlag = false;

	//IO flags
	bool ReadFlag, WriteFlag = false;


	//Bluetooth Functions
	DroidBT(void);
	String CheckBluetooth(void);
	std::list<String> GetBonded(void);
	void ConnectToDevice(String);
	void CloseConnection(void);
	void ReadFromDevice(bool);
	void WriteToDevice(void);



};
//---------------------------------------------------------------------------
#endif


