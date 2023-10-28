#pragma once
#ifndef SELF_VECTOR

namespace SelfDefined {

	template<typename Elem>
	class vector {

		static const size_t MIN_CHUNK_SIZE = 16;
		static const size_t MAX_CHUNK_NUM = 16;

		Elem* (chunks[MAX_CHUNK_NUM]);
		size_t currentChunkSize;
		size_t chunkNum;
		size_t elemNum;

		void shrink();

	public:

		vector();
		vector(int n, Elem e);
		~vector();
		vector(const vector& other);
		Elem& operator[](size_t i);
		const Elem& operator[](size_t i) const;
		vector<Elem>& operator=(const vector<Elem>& from);
		vector<Elem>& copy(const vector<Elem>& from) { *this = from; }
		size_t size() const;
		void push_back(Elem e);
		void pop_back();
	};

	template<typename Elem> vector<Elem>::vector(const vector<Elem>& other) {
		this->chunkNum = 0;
		*this = other;
		//other = vector<Elem>();
		//for (int i = 0; i < other.size();; i++)
			//this->//other.push_back((*this)[i]);
	}


	template<typename Elem> vector<Elem>::vector() {
		this->currentChunkSize = this->MIN_CHUNK_SIZE;
		this->chunkNum = 0;
		this->elemNum = 0;
	}

	template<typename Elem> vector<Elem>::vector(int n, Elem e) {
		size_t chunkSize = this->MIN_CHUNK_SIZE;
		for (; chunkSize < n; chunkSize *= 2)
			;
		this->currentChunkSize = chunkSize;
		this->chunks[0] = new Elem[chunkSize];
		this->chunkNum = 1;
		this->elemNum = n;

		for (int i = 0; i < n; i++)
			this->chunks[0][i] = e;
	}

	template<typename Elem> Elem& vector<Elem>::operator[](size_t i) {
		if (this->elemNum <= i)
			throw "Index out of range.";
		return this->chunks[i / (this->currentChunkSize)][i % (this->currentChunkSize)];
	}

	template<typename Elem> const Elem& vector<Elem>::operator[](size_t i) const {
		if (this->elemNum <= i)
			throw "Index out of range.";
		return this->chunks[i / (this->currentChunkSize)][i % (this->currentChunkSize)];
	}

	template<typename Elem> size_t vector<Elem>::size() const {
		return this->elemNum;
	}

	template<typename Elem> void vector<Elem>::shrink() {
		if (this->chunkNum != this->MAX_CHUNK_NUM)
			return;//Only work when all the chunks are allocated.

		//For now we merge every two chunk for this is easier.
		size_t nextChunkSize = currentChunkSize * 2;//Easy pick.
		for (int i = 0; i < this->chunkNum; i += 2)
		{
			Elem* newChunk = new Elem[nextChunkSize];
			int j = 0;
			for (int k = 0; k < this->currentChunkSize; j++, k++)
				newChunk[j] = this->chunks[i][k];
			for (int k = 0; k < this->currentChunkSize; j++, k++)
				newChunk[j] = this->chunks[i + 1][k];
			delete[]this->chunks[i];
			delete[]this->chunks[i + 1];
			this->chunks[i / 2] = newChunk;
		}
		this->chunkNum /= 2;
		this->currentChunkSize = nextChunkSize;

	}

	template<typename Elem> void vector<Elem>::pop_back() {
		this->elemNum--;
		//if (this->elemNum / this->currentChunkSize != this->chunkNum)
		if (this->elemNum <= (this->currentChunkSize * (this->chunkNum - 1)))
		{
			delete[] this->chunks[this->chunkNum - 1];
			this->chunkNum--;
		}
	}

	template<typename Elem> void vector<Elem>::push_back(Elem e) {
		if (this->elemNum == this->MAX_CHUNK_NUM * this->currentChunkSize)
			this->shrink();
		if (this->elemNum == this->chunkNum * this->currentChunkSize)
		{
			this->chunks[this->chunkNum] = new Elem[this->currentChunkSize];
			this->chunkNum++;
		}
		this->chunks[this->elemNum / (this->currentChunkSize)][this->elemNum % (this->currentChunkSize)] = e;
		this->elemNum++;
	}

}


template<typename Elem> SelfDefined::vector<Elem>& SelfDefined::vector<Elem>::operator=(const vector<Elem>& from) {
	for (int i = 0; i < this->chunkNum; i++)
		delete[] this->chunks[i];
	this->chunkNum = from.chunkNum;
	this->currentChunkSize = from.currentChunkSize;
	this->elemNum = from.elemNum;
	for (int i = 0; i < this->chunkNum; i++)
		this->chunks[i] = new Elem[this->currentChunkSize];
	for (size_t i = 0; i < this->elemNum; i++)
		(*this)[i] = from[i];
	//if (this->elemNum <= i)
		//throw "Index out of range.";
	return *this;
	//return this->chunks[i / (this->currentChunkSize)][i % (this->currentChunkSize)];
}

template<typename Elem> SelfDefined::vector<Elem>::~vector() {
	for (int i = 0; i < this->chunkNum; i++)
		delete[] this->chunks[i];
}




#endif // !SELF_VECTOR
