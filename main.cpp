#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <glog/logging.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

void init_log() {
    google::InitGoogleLogging("tmp");
    FLAGS_logtostderr = 4;
}

string log_config_file() {
    string config_file_path = "/Users/chendongsheng/github/json_prase/config/npu.json";
    ifstream in;
    in.open(config_file_path, ios_base::in);
    if(in.is_open() == false) {
        LOG(ERROR) << "file not exits";
        return "";
    }
    stringstream s_stream;
    s_stream << in.rdbuf();
    return s_stream.str();
}

int main()
{
    init_log();
    string file_info = log_config_file();
    json j_obj = json::parse(file_info);
    auto it = j_obj["npu"].begin();

    unordered_map<string, unordered_map<int, vector<string>>> container;

    while (it != j_obj["npu"].end()) {
        auto layer_name = it->at("layer_name").get<string>();
        if (it->at("condition").contains("support_list")) {
            DLOG(INFO) << layer_name << it->at("condition").at("support_list").size();
            for (int i = 0; i < it->at("condition").at("support_list").size(); i++) {
                container[layer_name][1].push_back(it->at("condition").at("support_list").at(i).get<string>());
            }
        } else {
            DLOG(INFO) << layer_name << " did`t have conditon";
            container[layer_name][1].push_back("all");
        }
        it++;
    }

    for (auto it : container) {
        LOG(INFO) << it.first;
        for (auto v : it.second[1]) {
            LOG(INFO) << "    " << v;
        }
    }


    return 0;
}
