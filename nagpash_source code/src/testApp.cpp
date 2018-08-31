#include "testApp.h"
#include <Windows.h>



    DWORD procStatus,inloop=1;
    int serByte = 0,gameFlag=0;

    const char* app="C:\\Windows\\System32\\cmd.exe";


    char* appname1="/C cd C:\\FruitNinja\&FruitNinja.exe";
    STARTUPINFO si1;
    PROCESS_INFORMATION pi1;


    char* appname2="/c C:\\fnkill.cmd";
    STARTUPINFO si2;
    PROCESS_INFORMATION pi2;

    char* appname3="/c C:\\delete.cmd";
    STARTUPINFO si3;
    PROCESS_INFORMATION pi3;


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);
    ofHideCursor();

    serial.enumerateDevices();
	serial.setup("COM8",9600);

    myMovie.loadMovie("movies/fingers.mp4");
	myMovie.play();



    //memory allocation to the structs process info and startup info
    memset(&si1, 0, sizeof(si1));
    memset(&pi1, 0, sizeof(pi1));
    memset(&si2, 0, sizeof(si2));
    memset(&pi2, 0, sizeof(pi2));
    memset(&si2, 0, sizeof(si3));
    memset(&pi2, 0, sizeof(pi3));



}

//--------------------------------------------------------------
void testApp::update(){
    myMovie.idleMovie();
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetHexColor(0xFFFFFF);
	myMovie.draw(0,0);


if(serial.available()>0)
serByte = serial.readByte();


/*
    stringstream reportStream;
    reportStream << "Serial byte: " <<serByte << endl
    << "gameFlag: "<<gameFlag<<endl;
	ofDrawBitmapString(reportStream.str(),100,100);
*/
    serial.flush(true,true);

if(serByte==1 && gameFlag==0)
{
    gameFlag=1;
    serial.flush(true,true);
    serByte=0;
    keyPressed('p');

}




}



//--------------------------------------------------------------
void testApp::keyPressed  (int key){

    switch(key){
        case 'p':

        myMovie.stop();


        //start appname1 i.e the game
        CreateProcessA(app,appname1,NULL,NULL, FALSE, 0, NULL, NULL, &si1, &pi1);

        //start appname2 which kills the game after some time through script...
        CreateProcessA(app, appname2, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2);




//monitoring the exit of the game either by timeout or forceful exit
//====================================================================
while(1)
{
inloop = GetExitCodeProcess(pi1.hProcess, &procStatus);
if(procStatus!=STILL_ACTIVE)
    {

    //get ready for next coin...
    gameFlag=0;
    serByte=0;
    serial.flush(true,true);


    //start movie from start...
    myMovie.setFrame(0);
    myMovie.play();

    CloseHandle( pi1.hProcess );
    CloseHandle( pi1.hThread );

    //if game gets terminated before timeout then kill the script else it will kill the new instance of the game
    TerminateProcess(pi2.hProcess,0);
    CloseHandle( pi2.hProcess );
    CloseHandle( pi2.hThread );

    //delete save files
    CreateProcessA(app, appname3, NULL, NULL, FALSE, 0, NULL, NULL, &si3, &pi3);
    CloseHandle( pi3.hProcess );
    CloseHandle( pi3.hThread );



    break;
}

}
//====================================================================


break;


    }

}



//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
