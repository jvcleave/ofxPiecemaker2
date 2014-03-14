#pragma once

#include "ofMain.h"

#include "ofxHttpUtils.h"
#include "ofxJSONElement.h"

class Group
{
public:
    Group()
    {
    
    }
    void print()
    {
        stringstream info;
        info << "id: "                  << id                   << "\n";
        info << "title: "               << title                << "\n";
        info << "created_at "           << created_at           << "\n";
        info << "created_by_user_id: "  << created_by_user_id   << "\n";
        
        ofLogVerbose(__func__) << "\n" << info.str();
    };
    int id;
    string title;
    string text;
    string created_at;
    int created_by_user_id;
};

class PiecemakerEvent
{
public:
    PiecemakerEvent()
    {
        id = -1;
        title = "";
        event_group_id = -1;
        utc_timestamp = "";
        duration = 0;
        type = "";
        
    }
    void print()
    {
        stringstream info;
        info << "event_group_id: "  << event_group_id     << "\n";
        info << "utc_timestamp: "   << utc_timestamp      << "\n";
        info << "duration "         << duration           << "\n";
        info << "type: "            << type               << "\n";
        info << "fields.size: "     << fields.size()      << "\n";
        ofLogVerbose(__func__) << "\n" << info.str();
    };
	int id;
    int event_group_id;
    string title;
	string utc_timestamp;
	long duration;
	string type;
	map<int, string> fields;

};

class LoginEventData
{
public:
	LoginEventData()
	{
        errorCode = -1;
        errorReason = "UNDEFINED";
		successful = false;
	}
    bool wasSuccessful()
    {
        return successful;
    }
    void setResponse(ofxHttpResponse response_)
    {
        this->response = response_;
        if(response.status <300 && response.status>=200)
        {
            successful = true;
        }else
        {
            errorCode = response.status;
            errorReason = response.reasonForStatus;
            successful = false;
        }
    }
    int errorCode;
    string errorReason;
private:
	ofxHttpResponse response;
    bool successful;
};

class GroupEventData
{
public:
    GroupEventData(vector<Group> groups_)
    {
        groups = groups_;
    }
    vector<Group> groups;
    
};

class PiecemakerEventData
{
public:
    PiecemakerEventData()
    {
    
    };
    vector<PiecemakerEvent> events;
};


class ofxPiecemaker2
{
public:
    ofxPiecemaker2();
    void setup(string url_);
    void login(string userEmail, string userPassword);
    void whoAmI();
    
    void listEvents(int groupId);
    
    
    void listGroups();
    void getGroup(int groupId);
    void createGroup(string groupTitle = "", string groupText = "");
    string url;
    string apiKey;
    

    ofEvent<LoginEventData> LOGIN;
    ofEvent<GroupEventData> GROUP;
    ofEvent<GroupEventData> LIST_GROUP;
    ofEvent<GroupEventData> CREATE_GROUP;
    ofEvent<PiecemakerEventData> LIST_EVENTS;
    
    string printResponse(ofxHttpResponse response);
#if 0
    static string getVersion();
    void printVersion();
    
    void logout();
    void listUsers();
    
    void createUser(string userName, string userEmail, string userPassword, string userToken);
    void getUser(int userId);
    void updateUser(int userId, string userName, string userEmail, string userPassword, string userToken);
    void deleteUser(int userId);
    //void listGroups();
    
    //void createGroup(string groupTitle, string groupText);
    void updateGroup(int groupId, HashMap groupData);
    void deleteGroup(int groupId);
    //void listEvents(int groupId);
    void listEventsOfType(int groupId, string eventType);
    void listEventsWithFields(Object ... args);
    void listEventsBetween(int groupId, Date from, Date to);
    void findEvents(int groupId, HashMap opts);
    void getEvent(int groupId, int eventId);
    void createEvent(int groupId, HashMap eventData);
    void updateEvent(int groupId, int eventId, HashMap eventData);
    void deleteEvent(int groupId, int eventId);
    void getSystemTime();
#endif
    
private:
    bool ensureApiKey();
    ofxHttpUtils httpUtils;    
    void onLoginResponse(ofxHttpResponse& response);
    void onListGroupsResponse(ofxHttpResponse& response);
    void onGetGroupResponse(ofxHttpResponse& response);
    void onCreateGroupResponse(ofxHttpResponse& response);
    void onListEventsResponse(ofxHttpResponse& response);
    void onWhoAmIResponse(ofxHttpResponse& response);
};