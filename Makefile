#WA:=-Wall -Wextra -DNDEBUG
WA:=-Wall -Wextra

base:baseDiscrete.h dsFactory.h aliasMethod.cpp aliasMethod.h aliasMethodFactory.cpp aliasMethodFactory.h stdDiscrete.cpp stdDiscrete.h stdDiscreteFactory.cpp stdDiscreteFactory.h naiveSample.cpp naiveSample.h naiveSampleFactory.cpp naiveSampleFactory.h snaiveSample.cpp snaiveSample.h snaiveSampleFactory.cpp snaiveSampleFactory.h twodNaive.cpp twodNaive.h twodNaiveFactory.cpp twodNaiveFactory.h threedSample.cpp threedSample.h threedSampleFactory.cpp threedSampleFactory.h randomNaive.cpp randomNaive.h randomNaiveFactory.cpp randomNaiveFactory.h treeSample.cpp treeSample.h treeSampleFactory.cpp treeSampleFactory.h refinedRandom.cpp refinedRandom.h refinedRandomFactory.cpp refinedRandomFactory.h randomCate.cpp randomCate.h randomCateFactory.cpp randomCateFactory.h star.cpp star.h starFactory.cpp starFactory.h heapSample.cpp heapSample.h heapSampleFactory.cpp heapSampleFactory.h stdDiscreteBoost.cpp stdDiscreteBoost.h stdDiscreteBoostFactory.cpp stdDiscreteBoostFactory.h lazyAliasMethod.cpp lazyAliasMethod.h lazyAliasMethodFactory.cpp lazyAliasMethodFactory.h testmain.cpp
	g++ -std=c++11 -O2 -o de testmain.cpp aliasMethod.cpp aliasMethodFactory.cpp stdDiscrete.cpp stdDiscreteFactory.cpp naiveSample.cpp naiveSampleFactory.cpp snaiveSample.cpp snaiveSampleFactory.cpp twodNaive.cpp twodNaiveFactory.cpp threedSample.cpp threedSampleFactory.cpp randomNaive.cpp randomNaiveFactory.cpp treeSample.cpp treeSampleFactory.cpp refinedRandom.cpp refinedRandomFactory.cpp randomCate.cpp randomCateFactory.cpp star.cpp starFactory.cpp heapSample.cpp heapSampleFactory.cpp stdDiscreteBoost.cpp stdDiscreteBoostFactory.cpp lazyAliasMethod.cpp lazyAliasMethodFactory.cpp -lboost_random $(WA)

clean:
	rm de

sptest:baseDiscrete.h dsFactory.h aliasMethod.cpp aliasMethod.h aliasMethodFactory.cpp aliasMethodFactory.h stdDiscrete.cpp stdDiscrete.h stdDiscreteFactory.cpp stdDiscreteFactory.h naiveSample.cpp naiveSample.h naiveSampleFactory.cpp naiveSampleFactory.h snaiveSample.cpp snaiveSample.h snaiveSampleFactory.cpp snaiveSampleFactory.h twodNaive.cpp twodNaive.h twodNaiveFactory.cpp twodNaiveFactory.h threedSample.cpp threedSample.h threedSampleFactory.cpp threedSampleFactory.h randomNaive.cpp randomNaive.h randomNaiveFactory.cpp randomNaiveFactory.h treeSample.cpp treeSample.h treeSampleFactory.cpp treeSampleFactory.h refinedRandom.cpp refinedRandom.h refinedRandomFactory.cpp refinedRandomFactory.h randomCate.cpp randomCate.h randomCateFactory.cpp randomCateFactory.h star.cpp star.h starFactory.cpp starFactory.h heapSample.cpp heapSample.h heapSampleFactory.cpp heapSampleFactory.h distributionSpeedTest.cpp distributionSpeedTest.h dtestmain.cpp
	g++ -std=c++11 -O2 -o de dtestmain.cpp distributionSpeedTest.cpp aliasMethod.cpp aliasMethodFactory.cpp stdDiscrete.cpp stdDiscreteFactory.cpp naiveSample.cpp naiveSampleFactory.cpp snaiveSample.cpp snaiveSampleFactory.cpp twodNaive.cpp twodNaiveFactory.cpp threedSample.cpp threedSampleFactory.cpp randomNaive.cpp randomNaiveFactory.cpp treeSample.cpp treeSampleFactory.cpp refinedRandom.cpp refinedRandomFactory.cpp randomCate.cpp randomCateFactory.cpp star.cpp starFactory.cpp heapSample.cpp heapSampleFactory.cpp $(WA)

gtest:baseDiscrete.h dsFactory.h aliasMethod.cpp aliasMethod.h aliasMethodFactory.cpp aliasMethodFactory.h stdDiscrete.cpp stdDiscrete.h stdDiscreteFactory.cpp stdDiscreteFactory.h naiveSample.cpp naiveSample.h naiveSampleFactory.cpp naiveSampleFactory.h snaiveSample.cpp snaiveSample.h snaiveSampleFactory.cpp snaiveSampleFactory.h twodNaive.cpp twodNaive.h twodNaiveFactory.cpp twodNaiveFactory.h threedSample.cpp threedSample.h threedSampleFactory.cpp threedSampleFactory.h randomNaive.cpp randomNaive.h randomNaiveFactory.cpp randomNaiveFactory.h treeSample.cpp treeSample.h treeSampleFactory.cpp treeSampleFactory.h refinedRandom.cpp refinedRandom.h refinedRandomFactory.cpp refinedRandomFactory.h randomCate.cpp randomCate.h randomCateFactory.cpp randomCateFactory.h graphtestmain.cpp
	g++ -std=c++11 -O2 -o de graphtestmain.cpp aliasMethod.cpp aliasMethodFactory.cpp stdDiscrete.cpp stdDiscreteFactory.cpp naiveSample.cpp naiveSampleFactory.cpp snaiveSample.cpp snaiveSampleFactory.cpp twodNaive.cpp twodNaiveFactory.cpp threedSample.cpp threedSampleFactory.cpp randomNaive.cpp randomNaiveFactory.cpp treeSample.cpp treeSampleFactory.cpp refinedRandom.cpp refinedRandomFactory.cpp randomCate.cpp randomCateFactory.cpp $(WA)
	
ggtest:baseDiscrete.h dsFactory.h aliasMethod.cpp aliasMethod.h aliasMethodFactory.cpp aliasMethodFactory.h stdDiscrete.cpp stdDiscrete.h stdDiscreteFactory.cpp stdDiscreteFactory.h naiveSample.cpp naiveSample.h naiveSampleFactory.cpp naiveSampleFactory.h snaiveSample.cpp snaiveSample.h snaiveSampleFactory.cpp snaiveSampleFactory.h twodNaive.cpp twodNaive.h twodNaiveFactory.cpp twodNaiveFactory.h threedSample.cpp threedSample.h threedSampleFactory.cpp threedSampleFactory.h randomNaive.cpp randomNaive.h randomNaiveFactory.cpp randomNaiveFactory.h treeSample.cpp treeSample.h treeSampleFactory.cpp treeSampleFactory.h refinedRandom.cpp refinedRandom.h refinedRandomFactory.cpp refinedRandomFactory.h randomCate.cpp randomCate.h randomCateFactory.cpp randomCateFactory.h graphtestmain.cpp
	g++ -g -std=c++11 -O2 -o de graphtestmain.cpp aliasMethod.cpp aliasMethodFactory.cpp stdDiscrete.cpp stdDiscreteFactory.cpp naiveSample.cpp naiveSampleFactory.cpp snaiveSample.cpp snaiveSampleFactory.cpp twodNaive.cpp twodNaiveFactory.cpp threedSample.cpp threedSampleFactory.cpp randomNaive.cpp randomNaiveFactory.cpp treeSample.cpp treeSampleFactory.cpp refinedRandom.cpp refinedRandomFactory.cpp randomCate.cpp randomCateFactory.cpp $(WA)
	
linear:baseDiscrete.h dsFactory.h aliasMethod.cpp aliasMethod.h aliasMethodFactory.cpp aliasMethodFactory.h stdDiscrete.cpp stdDiscrete.h stdDiscreteFactory.cpp stdDiscreteFactory.h naiveSample.cpp naiveSample.h naiveSampleFactory.cpp naiveSampleFactory.h snaiveSample.cpp snaiveSample.h snaiveSampleFactory.cpp snaiveSampleFactory.h twodNaive.cpp twodNaive.h twodNaiveFactory.cpp twodNaiveFactory.h threedSample.cpp threedSample.h threedSampleFactory.cpp threedSampleFactory.h randomNaive.cpp randomNaive.h randomNaiveFactory.cpp randomNaiveFactory.h treeSample.cpp treeSample.h treeSampleFactory.cpp treeSampleFactory.h refinedRandom.cpp refinedRandom.h refinedRandomFactory.cpp refinedRandomFactory.h randomCate.cpp randomCate.h randomCateFactory.cpp randomCateFactory.h star.cpp star.h starFactory.cpp starFactory.h heapSample.cpp heapSample.h heapSampleFactory.cpp heapSampleFactory.h stdDiscreteBoost.cpp stdDiscreteBoost.h stdDiscreteBoostFactory.cpp stdDiscreteBoostFactory.h linearModel.cpp
	g++ -std=c++11 -O2 -o de linearModel.cpp aliasMethod.cpp aliasMethodFactory.cpp stdDiscrete.cpp stdDiscreteFactory.cpp naiveSample.cpp naiveSampleFactory.cpp snaiveSample.cpp snaiveSampleFactory.cpp twodNaive.cpp twodNaiveFactory.cpp threedSample.cpp threedSampleFactory.cpp randomNaive.cpp randomNaiveFactory.cpp treeSample.cpp treeSampleFactory.cpp refinedRandom.cpp refinedRandomFactory.cpp randomCate.cpp randomCateFactory.cpp star.cpp starFactory.cpp heapSample.cpp heapSampleFactory.cpp stdDiscreteBoost.cpp stdDiscreteBoostFactory.cpp -lboost_random $(WA)

bandit:baseDiscrete.h dsFactory.h aliasMethod.cpp aliasMethod.h aliasMethodFactory.cpp aliasMethodFactory.h stdDiscrete.cpp stdDiscrete.h stdDiscreteFactory.cpp stdDiscreteFactory.h naiveSample.cpp naiveSample.h naiveSampleFactory.cpp naiveSampleFactory.h snaiveSample.cpp snaiveSample.h snaiveSampleFactory.cpp snaiveSampleFactory.h twodNaive.cpp twodNaive.h twodNaiveFactory.cpp twodNaiveFactory.h threedSample.cpp threedSample.h threedSampleFactory.cpp threedSampleFactory.h randomNaive.cpp randomNaive.h randomNaiveFactory.cpp randomNaiveFactory.h treeSample.cpp treeSample.h treeSampleFactory.cpp treeSampleFactory.h refinedRandom.cpp refinedRandom.h refinedRandomFactory.cpp refinedRandomFactory.h randomCate.cpp randomCate.h randomCateFactory.cpp randomCateFactory.h star.cpp star.h starFactory.cpp starFactory.h heapSample.cpp heapSample.h heapSampleFactory.cpp heapSampleFactory.h bandit.cpp
	g++ -std=c++11 -O2 -o de bandit.cpp aliasMethod.cpp aliasMethodFactory.cpp stdDiscrete.cpp stdDiscreteFactory.cpp naiveSample.cpp naiveSampleFactory.cpp snaiveSample.cpp snaiveSampleFactory.cpp twodNaive.cpp twodNaiveFactory.cpp threedSample.cpp threedSampleFactory.cpp randomNaive.cpp randomNaiveFactory.cpp treeSample.cpp treeSampleFactory.cpp refinedRandom.cpp refinedRandomFactory.cpp randomCate.cpp randomCateFactory.cpp star.cpp starFactory.cpp heapSample.cpp heapSampleFactory.cpp $(WA)
