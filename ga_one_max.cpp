#include <random>
#include <iostream>

void toNextStep(int **genes, int length, int num, double *score);
void calculateScore(int **genes, int length, int num, double *score);
void doCrossing1(int **genes,int length, int num);
void outputScore(double *score,int num);

int main(int argc, char const *argv[])
{
	int length,num,ite;
	length = 10;
	num = 10;
	ite = 100;
	int **genes = new int*[num];
	double *score = new double[num];
	std::random_device rnd;
	std::mt19937 mt(rnd());
	for (int i = 0; i < num; i++){
		genes[i] = new int[length];
		for (int j = 0; j < length; j++)
		{
			if((mt()%2)==1){
				genes[i][j] = 1;
			}else{
				genes[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < ite; ++i)
	{
		toNextStep(genes, length, num, score);
		if((i+1)%10 == 0){
			outputScore(score,num);
		}
	}
	return 0;
}


//GAを1ステップ行う
void toNextStep(int **genes, int length, int num, double *score){
	doCrossing1(genes, num, length);
	calculateScore(genes,length, num, score);
}
//各個体のスコアを計算
void calculateScore(int **genes, int length, int num, double *score){
	int tmp;
	for (int i = 0; i < num; i++){
		tmp=0;
		for (int j = 0; j < length; j++){
			tmp = tmp + genes[i][j];
		}
		score[i] = static_cast<double>(tmp) / length;
	}
}
//genes内の連続する個体で交叉を行う(一点交叉)
void doCrossing1(int **genes,int length,int num){
	int tmp,half;
	half = length/2;
	for (int i = 0; i < num-1; i+=2)
	{
		for (int j = 0; j < half; ++j)
		{
			tmp = genes[i][j];
			genes[i][j] = genes[i+1][j];
			genes[i+1][j] = tmp;
		}
	}
}

//スコアを出力
void outputScore(double *score,int num){
	double ave,max,min;
	ave=0;
	max = 0;
	min = 1;
	for (int i = 0; i < num; ++i){
		ave = ave + score[i];
		if(max < score[i]){
			max = score[i];
		}
		if(min > score[i]){
			min = score[i];
		}
	}
	ave = ave / num;
	std::cout << "ave: " << ave << std::endl;
	std::cout << "max: " << max << std::endl;
	std::cout << "min: " << min << std::endl;
}