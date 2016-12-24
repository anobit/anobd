//---------------------------------------------------------------------------

#pragma hdrstop

#include "btthread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//Constructor for Threading Class
//Contains a pointer to the actual bluetooth class
//WARNING: potentially unsafe to multithread, because accessing common object
//my module doesn't expect multiple simultaneous IO and I disable thread creation buttons if one has been created
DroidBTConnectThread::DroidBTConnectThread(DroidBT *m_DroidBT)  : TThread(false)
{
	m_DroidBTPtr = m_DroidBT;
}
//---------------------------------------------------------------------------


//Constructor for Threading Class
//Contains a pointer to the actual bluetooth class
//WARNING: potentially unsafe to multithread, because accessing common object
//my module doesn't expect multiple simultaneous IO and I disable thread creation buttons if one has been created
DroidBTRequestThread::DroidBTRequestThread(DroidBT *m_DroidBT)  : TThread(false)
{
	m_DroidBTPtr = m_DroidBT;
}
//---------------------------------------------------------------------------


//Constructor for Threading Class
//Contains a pointer to the actual bluetooth class
//WARNING: potentially unsafe to multithread, because accessing common object
//my module doesn't expect multiple simultaneous IO and I disable thread creation buttons if one has been created
DroidBTResponseThread::DroidBTResponseThread(DroidBT *m_DroidBT)  : TThread(false)
{
	m_DroidBTPtr = m_DroidBT;
}
//---------------------------------------------------------------------------


 /*
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
						Start of Android Bluetooth Threading Function Declaration
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
*/

//Thread to run blocking socket connection function
void __fastcall DroidBTConnectThread::Execute()
{
	//Connect, create IOStreams, cancel discovery to save bandwidth, and start the IO thread
	//Let user know is failed or successful
	if(m_DroidBTPtr->ConnectFlag == true){



		try {
			m_DroidBTPtr->m_JBluetoothSocket->connect();
			m_DroidBTPtr->m_JInputStream = m_DroidBTPtr->m_JBluetoothSocket->getInputStream();
			m_DroidBTPtr->m_JOutputStream = m_DroidBTPtr->m_JBluetoothSocket->getOutputStream();
			m_DroidBTPtr->m_JBluetoothAdapter->cancelDiscovery();
			ShowMessage("Succesfully connected to Bluetooth");
		}
		catch (...) {
			ShowMessage("Unable to succesfully connect Bluetooth");
		}

		m_DroidBTPtr->ConnectFlag = false;
		return;
	}

}


	  /*
//Thread to run blocking Write Request function
void __fastcall DroidBTRequestThread::Execute()
{
	//Output byte buffer
	_di_JByteBuffer WriteBytesBuffer= TJByteBuffer::JavaClass->allocate(32);


								//You might want a for loop and copy an array in here, or do whatever you need for your project
								//You don't have to use a JByteBuffer, but I'm used to it lol
				WriteBytesBuffer->put(INDEX, System::Byte(**YOUR BYTE DATA HERE**));

						 //You can also use write(ONEBYTETOWRITE) and write(BYTE[]), it may be a bit tricky to find what it will accept as a byte array, but a
						//pointer to a char array works, if you don't want to use a JByteBuffer
			m_DroidBTPtr->m_JOutputStream->write(WriteBytesBuffer->array(), INDEX, NUMBYTESTOWRITE);


		}
		catch (...) {
			ShowMessage("Exception thrown from reques thread");
		}
	}

}   */



//Thread to run blocking Read Response function
void __fastcall DroidBTResponseThread::Execute(){

	//IO Variables
	_di_JByteBuffer ReadBytesBuffer = TJByteBuffer::JavaClass->allocate(32);


	while(true){
	   try{
                        //Might need to throw around some asterisks inside that read, this is edited and untested from my working code which reads to another
                        //object.  Read works like write in that you can use read() to get one byte, and read(BYTE[], INDEX, NUMBYTESTOREAD)
		        m_DroidBTPtr->m_JInputStream->read(m_DroidBTPtr->Response));

		}
		catch (...) {
				ShowMessage("Exception thrown from read response thread");
		}
	}


}
//---------------------------------------------------------------------------


 /*
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
						End of Android Bluetooth Threading Function Declaration
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
*/