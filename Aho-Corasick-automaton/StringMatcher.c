#include "StringMatcher.h"
#include "malloc.h"
#include "time.h"
#include "stdlib.h"
#pragma warning(disable:4996)
void matchString(StringMatcher * this, char * str, char * pat)
{
	clock_t start, end;
	double duration;
	char *ptn;
	if (!openPatFile(this->io_, pat)) {
		printf("Failed to open %s\n", pat);
		return;
	}

	if (!openStrFile(this->io_, str)) {
		printf("Failed to open %s\n", str);
		return;
	}

	start = clock();
	while ((ptn = getPattern(this->io_)) != NULL) {
		insertKeywordACA(this->aca_, ptn);
	}
	end = clock();
 duration = ((double)end - start) / CLOCKS_PER_SEC;
	printf("建立自动机时间 time=%f seconds\n", duration);

	start = clock();
	_addFailPointer(this->aca_);
	end = clock();
	 duration = ((double)end - start) / CLOCKS_PER_SEC;
	printf("建立 Fail 指针时间 time=%f seconds\n", duration);

	start = clock();
	while ((str = getString(this->io_)) != NULL) {
		matchStringACA(this->aca_, str);
	}
	end = clock();
	 duration = ((double)end - start) / CLOCKS_PER_SEC;
	printf("匹配时间 time=%f seconds\n", duration);
}
int _cmp_key_count(const key_count *a, const key_count *b)
{
	return a->count < b->count ? 1 : -1;
}

void outPutResult(StringMatcher *this, char * file_name)
{
	long total_num = this->aca_->key_num_;
	char **keywords = this->aca_->keyword_;
	long *count = this->aca_->key_count_;
	key_count *index = (key_count *)(malloc(sizeof(key_count)*total_num));

	// Initialize array.
	long i = 0;
	for (i = 0; i < total_num; ++i) {
		index[i].count = count[i];
		index[i].keyId = i;
	}
	qsort(index, total_num, sizeof(key_count), _cmp_key_count);
	//[DICT_SIZE][MAX_WORD_LEGNTH]
	printf("统计结果:\n");
	FILE *file = fopen(file_name, "w");
	if (!file) {
		printf("Failed to open output file");
		return;
	}
	for (i = 0;i < total_num;++i) {
		printf("%s %d\n", this->aca_->keyword_[index[i].keyId], this->aca_->key_count_[index[i].keyId]);
		fprintf(file, "%s %d\n", this->aca_->keyword_[index[i].keyId], this->aca_->key_count_[index[i].count]);
	}
	fclose(file);
	free(index);
}


void _Qsort(StringMatcher *this, int a[], int low, int high)
{
	if (low >= high)
	{
		return;
	}
	int first = low;
	int last = high;
	int key = a[first];/*用字表的第一个记录作为枢轴*/

	while (first < last)
	{
		while (first < last && this->aca_->key_count_[a[last]] >= this->aca_->key_count_[key])
		{
			--last;
		}

		a[first] = a[last];/*将比第一个小的移到低端*/

		while (first < last && this->aca_->key_count_[a[first]] <= this->aca_->key_count_[key])
		{
			++first;
		}

		a[last] = a[first];
		/*将比第一个大的移到高端*/
	}
	a[first] = key;/*枢轴记录到位*/
	_Qsort(this, a, low, first - 1);
	_Qsort(this, a, first + 1, high);
}

void _constructStringMatcher(StringMatcher * this)
{
	this->aca_ = (ACAutomaton *)malloc(sizeof(ACAutomaton));
	_constructACA(this->aca_);
	this->io_ = (IOManager *)malloc(sizeof(IOManager));
	_constructIO(this->io_);
}


void _deconstructStringMatcher(StringMatcher *this)
{
	if (this->aca_ != NULL) {
		_deconstructACA(this->aca_);
		free(this->aca_);
	}
	if (this->io_ != NULL) {
		_deconstructIO(this->io_);
		free(this->io_);
	}
}
