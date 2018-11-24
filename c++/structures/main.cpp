#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ostream>
#include <libgen.h>

using namespace std;

#define RESULT_OK               0
#define RESULT_INVALID_CMD      1
#define RESULT_INVALID_TENANT   2
#define RESULT_INVALID_URL      3



/**
 * Structure returned by function.
 */

struct bin_entry {
    string      ip;
    int         port;
};

using bin_map       = map<string, bin_entry>;
using tenant_map    = map<int, const bin_map &>;

bin_entry * lookupTenantURL(int tenantId,
        const string & url,
        int * error = nullptr);

/**
 * Bins map the URL to a node entry which specifies IP address and port #
 */

bin_map map1 = {
        { "/home/user/bob",         { "10.10.1.16",    80 },    },
        { "/user/admin/system",     { "192.168.0.150", 22 },    },
        { "/data/customer/us",      { "172.120.33.24", 8000 },  },
};

bin_map map2 = {
        { "/home/user/phil",        { "10.10.1.16",    80 },    },
        { "/user/root/sysdir",      { "192.168.0.155", 22 },    },
        { "/data/customer/canada",  { "172.120.120.1", 8000 },  },
};

/**
 * Tenant map links tenant ID to a bin_map
 */

tenant_map  tenants = {
        { 1, map1, },
        { 2, map2, },
};

/**
 * Dump the bin_map to the io stream.
 * @param strm
 * @param binMap
 * @return
 */
ostream & operator << (ostream & strm, const bin_map & binMap) {
    cout << "contains " << binMap.size() << " entries\n";

    for (auto const & entry : binMap) {
        strm << "URL   : " << entry.first << '\n';
        strm << "IP    : " << entry.second.ip << '\n';
        strm << "PORT  : " << entry.second.port << '\n';
    }

    return strm;
}

/**
 * Dump the tenant_map to the io stream.
 * @param strm
 * @param tenantMap
 * @return
 */
ostream & operator << (ostream & strm, const tenant_map & tenantMap) {
    strm << "contains " << tenantMap.size() << " entries\n";

    for (auto const & tenantEntry : tenantMap) {
        strm << "Tenant ID  : " << tenantEntry.first << '\n';
        strm << tenantEntry.second;
    }

    return strm;
}

/**
 * Look up tenant and URL and return bin_entry pointer.
 *
 * @param tenantId
 * @param url
 * @return
 */
bin_entry * lookupTenantURL(int tenantId, const string & url, int * error) {
    bin_entry * binValue = nullptr;

    auto const & whichTenant = tenants.find(tenantId);

    if (whichTenant != tenants.end()) {
        auto const & thisBinMap = (*whichTenant).second;
        auto const & whichBin   = thisBinMap.find(url);

        /* If the url is found then allocate new bin_entry and fill it in */
        if (whichBin != thisBinMap.end()) {
            binValue = new bin_entry;
            *binValue = (*whichBin).second;
        } else {
            cerr << "ERROR: Unable to locate desired URL '" << url << "'\n";
            if (error) {
                *error = RESULT_INVALID_URL;
            }
        }
    } else {
        cerr << "ERROR: Invalid tenant ID " << tenantId << '\n';
        if (error) {
            *error = RESULT_INVALID_TENANT;
        }
    }

    return binValue;
}

/**
 * Print usage message to the user.
 * @param cmd
 */
static void usage(const string & fullcmd) {
    string cmd = basename(const_cast<char *>(fullcmd.c_str()));

    cout << cmd << " dump\n";
    cout << cmd << " find [tenantid] [url]\n";
}

int main(int argc, char * argv[]) {
    std::cout << "Data Structure Example" << std::endl;

    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    string userCmd = argv[1];

    if (userCmd == "dump") {
        cout << "-- tenant dump --------" << '\n';
        cout << tenants;
    } else if (userCmd == "find") {
        if (argc < 4) {
            cerr << "Must specify tenant ID and URL to find.\n";
            return 1;
        }

        string tenant_id, url;
        int tid   = -1;

        /* Get the id and the url from the arguments */
        tenant_id = argv[2];
        url       = argv[3];

        try {
            tid = stoi(tenant_id);
        }
        catch (invalid_argument & e) {
            cerr << "Tenant ID must be all numeric.\n";
            return RESULT_INVALID_TENANT;
        }

        auto error = RESULT_OK;
        auto * thisEntry = lookupTenantURL(stoi(tenant_id), url, &error);

        if (thisEntry) {
            cout << "FOUND TENANT #1 URL '/data/customer/us'\n";
            cout << "IP : " << thisEntry->ip << " port # " << thisEntry->port << '\n';
            delete thisEntry;
        } else {
            string component;
            switch (error) {
                case RESULT_INVALID_TENANT:
                    component = "tenant";
                    break;
                case RESULT_INVALID_URL:
                    component = "url";
                    break;
                default:break;
            }

            cout << "Unable to locate " << component << " in map.\n";

            return error;
        }
    } else {
        cerr << "Unrecognized command option '" << userCmd << "'\n";
        return RESULT_INVALID_CMD;
    }

    return 0;
}