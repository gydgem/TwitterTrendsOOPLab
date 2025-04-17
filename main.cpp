#include <filesystem>
#include "handlers/ParserHandler.h"
#include "handlers/DataProcessingHandler.h"
#include "algorithms/sentiment_score.h"
#include "handlers/renderHandler.h"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    // Пути по умолчанию
    std::string statesPath = "resources/data/states.json";
    std::string tweetsPath = "resources/data/cali_tweets2014.txt"; // default
    std::string sentimentsPath = "resources/data/sentiments.csv";

    if(argc > 1) {
        tweetsPath = argv[1];
    }

    try {
        // Создаем папку для результатов если ее нет
        fs::create_directory("res");

        {
            handler::ParserHandler parserHandler(statesPath, tweetsPath, sentimentsPath);
            parserHandler.loadAll();
            handler::DataProcessingHandler dataProcessingHandler(parserHandler.getStates(),
                                                                 parserHandler.getTweets(),
                                                                 parserHandler.getSentiments());
            dataProcessingHandler.calculateAll();

            handler::renderHandler renderHandler(dataProcessingHandler.getScaledStatesPolygons(),
                                                 dataProcessingHandler.getScaledTweetsPoints(),
                                                 dataProcessingHandler.getSentimentTweets(),
                                                 dataProcessingHandler.getSentimentStates(),
                                                 parserHandler.getStates());
            renderHandler.drawAll();

            fs::path inputPath(tweetsPath);
            std::string outputName = "res/" + inputPath.stem().string() + ".png";
            cv::imwrite(outputName, renderHandler.getImage());

            cv::namedWindow("Twitter Sentiment Analysis", cv::WINDOW_AUTOSIZE);
            cv::imshow("Twitter Sentiment Analysis", renderHandler.getImage());
            cv::waitKey(0);
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}