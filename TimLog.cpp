#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

// Custom Tim logger because fuck it that's why

namespace TimLog
{
    static class Emitter
    {
        // Strategies:
        //  - check if file we're writing to is intended for this program, encode api's
    public:
        void Log(char *message);

    private:
        bool _master_Log = false;
        int _box_OS = 0;
        int _app;
        std::ofstream _file;
        std::vector<std::tuple<char *, int>> _externLogsManager;

        bool _masterLoggerConnection; // ensure master logger is reachable before attempting to emmit messages

        void init_file();
        void test_master_logger_connection();
        void emit_master_log();
        void log_local();
        // 1. See if file we write to exists, i
        // 2.

        Emitter(int os, int app, bool masterLog) : _master_Log(masterLog), _box_OS(os), _app(app) {};
        ~Emitter() {
            // make sure all logs have completed being logged, file closed, and all master logs succeeded in sending
        };
    };

    // this is for the master server to receive messages from boxes/api's
    class Receiver
    {
        // open handler socket for each message received from distributed processes
    };

    // used when utilizing TimLog service
    struct
    {
        int INFO = 0;
        int DEV = 1;
        int EXTERN_DEBUG = 2;
        int ERROR = 3;
    } log_Level;

    // used when creating TimLog instance
    struct
    {
        int REVERSE_PROXY = 0;
        int API_GATEWAY = 1;
        int LOG_MESSENGER = 2;
        int BOX_MANAGER = 3;
    } caller_App;

    struct
    {
        int LINUX_BOX = 0;
        int WINDOWS_BOX = 0;
    } box_OS;

    // used for managing processes and extending functionality around retries and fault handling
    struct
    {
        int NOT_SENT = 0;
        int EN_EOUTE = 1;
        int SUCCESS = 2;
        int FAILURE = 3;
    } master_log_emitter_status;

};

void TimLog::Emitter::init_file() {
    // make sure file exists
    // ensure file not in use by separate process
};

void TimLog::Emitter::test_master_logger_connection() {
};

void TimLog::Emitter::Log(char *message) {

};
void TimLog::Emitter::emit_master_log() {
    // make sure connection to external site is handled

    // **note: make sure 'creating websocket connection' is handled in a class
};
void TimLog::Emitter::log_local() {
    // make sure file is open
    // format entry
    // write entry
    //
};
