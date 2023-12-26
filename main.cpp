//
// Created by hy on 2023/12/26.
//

#include "thunder_sdk.h"

using namespace tc;

int main(int argc, char** argv) {
    ThunderSdkParams params{
        .ssl_ = false,
        .ip_ = "127.0.0.1",
        .port_ = 9002,
        .req_path_ = "/media",
    };
    ThunderSdk sdk;
    sdk.Init(params);
    sdk.Start();

    std::this_thread::sleep_for(std::chrono::milliseconds (1000));

    return 0;
}