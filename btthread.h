//---------------------------------------------------------------------------

#ifndef btthreadH
#define btthreadH
//---------------------------------------------------------------------------
#endif

#include<system.classes.hpp>

#include "btrfcomm.h"
class DroidBT;
//class DroidBT;

//Threading Class to handle blocking bluetooth Connect functions
//---------------------------------------------------------------------------
class DroidBTConnectThread : public TThread
{
public:
 DroidBTConnectThread( DroidBT *m_DroidBT);
 void __fastcall Execute();
 DroidBT * m_DroidBTPtr;

};
//---------------------------------------------------------------------------


//Threading Class to handle blocking bluetooth Read functions
//---------------------------------------------------------------------------
class DroidBTResponseThread : public TThread
{
public:
 DroidBTResponseThread( DroidBT *m_DroidBT);
 void __fastcall Execute();
 DroidBT * m_DroidBTPtr;

};
//---------------------------------------------------------------------------



//Threading Class to handle blocking bluetooth Write functions
//---------------------------------------------------------------------------
class DroidBTRequestThread : public TThread
{
public:
 DroidBTRequestThread( DroidBT *m_DroidBT);
 void __fastcall Execute();
 DroidBT * m_DroidBTPtr;

};
//---------------------------------------------------------------------------
