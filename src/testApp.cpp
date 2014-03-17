#include "testApp.h"




#define __func__ __PRETTY_FUNCTION__
//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetLogLevel("ofxHttpUtils", OF_LOG_SILENT);
    ofSetLogLevel("ofAppGLFWWindow", OF_LOG_SILENT);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofAddListener(api.LOGIN, this, &testApp::onAPIConnect);
    api.setup("http://piecemaker2-test.herokuapp.com/api/v1");
   // api.login("SuperAdmin", "SuperAdmin");
    api.login("test@fake.motionbank.org", "test@fake.motionbank.org");

}



void testApp::onAPIConnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &testApp::onAPIConnect);
    
    if(e.wasSuccessful())
    {
        ofAddListener(api.LIST_GROUPS, this, &testApp::onListGroups);
        api.listGroups();
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }

}

void testApp::onAPIDisconnect(LoginEventData& e)
{
    ofRemoveListener(api.LOGIN, this, &testApp::onAPIDisconnect);
    
    if(e.wasSuccessful())
    {
        ofLogVerbose() << "LOGOUT PASS";
    }else
    {
        ofLogError(__func__) << "errorCode: " << e.errorCode << " reason: " << e.errorReason;
    }
    
}

void testApp::onGetUser(UserEventData& e)
{
     ofRemoveListener(api.GET_USER, this, &testApp::onGetUser);
    ofLogVerbose(__PRETTY_FUNCTION__) << "";
    e.print();
}


void testApp::getUser(int userID)
{
    ofAddListener(api.GET_USER, this, &testApp::onGetUser);
    api.getUser(userID);
}

void testApp::logout()
{
    ofAddListener(api.LOGOUT, this, &testApp::onAPIDisconnect);
    api.logout();
}

void testApp::onListGroups(GroupEventData& e)
{
    ofLogVerbose(__func__) << "groups.size(): " << e.groups.size();
    ofRemoveListener(api.LIST_GROUPS, this, &testApp::onListGroups);
    if (e.groups.empty())
    {
       // createGroup();
    }else
    {
        groupsToDelete = e.groups;
        for (size_t i=0; i<e.groups.size(); i++)
        {
            Group& group    = e.groups[i];
            group.print();
            api.getGroup(group.id);
            listEventsForGroup(group.id);
        }        
    }
}
static const char alphanum[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";



char genRandom()
{
    int stringLength = sizeof(alphanum) - 1;
    return alphanum[rand() % stringLength];
}


void testApp::createRandomGroups()
{
    ofAddListener(api.CREATE_GROUP, this, &testApp::onGroupCreated);
    
    for (size_t i=0; i<2; i++)
    {
        string title = "title ";
        string text = "text ";
        for(unsigned int j = 0; j < 10; ++j)
        {
            title += genRandom();
            text += genRandom();
        }
        api.createGroup(title, text);
    }
    
}

void testApp::onGroupCreated(GroupEventData& e)
{
    cout << "onGroupCreated" << endl;
    ofRemoveListener(api.CREATE_GROUP, this, &testApp::onGroupCreated);
    if (!e.groups.empty())
    {
        
        
        
    }
    
}
void testApp::listEventsForGroup(int groupId)
{
    ofLogVerbose(__func__) << "groupId: " << groupId;
    ofAddListener(api.LIST_EVENTS, this, &testApp::onListEvents);
    api.listEvents( groupId );
}

void testApp::onListEvents(PiecemakerEventData& e)
{
    ofLogVerbose(__func__) << "events.size(): " << e.events.size();
    ofRemoveListener(api.LIST_EVENTS, this, &testApp::onListEvents);
    if(!e.events.empty())
    {
        for (size_t i=0; i<e.events.size(); i++)
        {
            PiecemakerEvent& event    = e.events[i];
            event.print();
        }
    }
    
}
void testApp::onGroupDeleted(GroupEventData& e)
{
    
}


void testApp::deleteAllGroups()
{
    ofAddListener(api.DELETE_GROUP, this, &testApp::onGroupDeleted);
    if (!groupsToDelete.empty())
    {
        for (size_t i=0; i<groupsToDelete.size(); i++)
        {
            api.deleteGroup(groupsToDelete[i].id);
        }
        groupsToDelete.clear();
    }else
    {
        ofLogError() << "NO GROUPS TO DELETE - RELISTING";
        api.listGroups();
    }
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'c')
    {
        createRandomGroups();
       
    }
    if (key == 'D')
    {
        deleteAllGroups();
       
    }
    if (key == 'x')
    {
        logout();
        
    }
    if (key == 'u')
    {
        getUser(3);
        
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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