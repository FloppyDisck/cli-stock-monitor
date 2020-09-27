cc_binary(
    name = "main",
    srcs = glob(["*.cpp","*.hpp"]),
    deps = [
        "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
    ],
    linkopts = ["-lncurses"],
)
