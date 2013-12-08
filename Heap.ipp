#include <string>

template<class Pri, class T>
Heap<Pri,T>::Heap(){
	backingArray = new std::pair<Pri,T>[START_SIZE];
	arrSize = START_SIZE;
	numItems=0;
}

template<class Pri, class T>
Heap<Pri,T>::~Heap(){
	delete[] backingArray;
}

template<class Pri, class T>
void Heap<Pri,T>::grow(){
	std::pair<Pri, T>* replacement = new std::pair<Pri,T>[arrSize*2];
	if(replacement==NULL)
          throw std::string("You have run out of memory, sorry.");

	for(int i=0; i<numItems; i++)
          replacement[i] = backingArray[i];

	delete[] backingArray;
    backingArray = replacement;  
}

template<class Pri, class T>
void Heap<Pri,T>::add(std::pair<Pri,T> toAdd){//items are just added one by one in order.
	if(numItems==arrSize)
		grow();

	backingArray[numItems] = toAdd; //1st gets added at [0], 2nd gets added at [1], etc.
	bubbleUp(numItems); //because bubbleUp is called before numItems++, we can get away with not reducing the index by 1.
	numItems++;
}

template<class Pri, class T>
void Heap<Pri,T>::bubbleUp(unsigned long index){//yeah sorry I don't recurse unless it is a severely complicated case.
	while(index>0){
		if(backingArray[index].first < backingArray[(index-1)/2].first){ //compares internal priorities
			Pri tempPri = backingArray[index].first;
			T tempT = backingArray[index].second;
			backingArray[index].first = backingArray[(index-1)/2].first;
		    backingArray[index].second = backingArray[(index-1)/2].second;
			backingArray[(index-1)/2].first = tempPri;
			backingArray[(index-1)/2].second = tempT;
			index=(index-1)/2; //integer division allows this to work for both cases of x.0 and x.5 results due to rounding down.
		}
		else
			return;
	}
}

template<class Pri, class T>
void Heap<Pri,T>::trickleDown(unsigned long index){//yeah sorry I don't recurse unless it is a severely complicated case.
	while((int)((index+1)*2) < numItems){
		if(backingArray[index*2 +1].first < backingArray[(index+1)*2].first){
			if(backingArray[index].first > backingArray[index*2 +1].first){
				Pri tempPri = backingArray[index].first;
				T tempT = backingArray[index].second;
				backingArray[index].first = backingArray[index*2 +1].first;
				backingArray[index].second = backingArray[index*2 +1].second;
				backingArray[index*2 +1].first = tempPri;
				backingArray[index*2 +1].second = tempT;
				index = index*2 +1;
			}//if priority of top node is not greater than the lesser of the two children, then do nothing
			else
				return;
		}else{ /*outter if*/
			if(backingArray[index].first > backingArray[(index+1) *2].first){
				Pri tempPri = backingArray[index].first;
				T tempT = backingArray[index].second;
				backingArray[index].first = backingArray[(index+1) *2].first;
				backingArray[index].second = backingArray[(index+1) *2].second;
				backingArray[(index+1) *2].first = tempPri;
				backingArray[(index+1) *2].second = tempT;
				index = (index+1)*2;
			}//if priority of top node is not greater than the lesser of the two children, then do nothing
			else
				return;
		}//end else
	}//end while

	if(!((int)index*2 +1 < numItems-1))
		return;
	if(backingArray[index].first > backingArray[index*2 +1].first){
		Pri tempPri = backingArray[index].first;
		T tempT = backingArray[index].second;
		backingArray[index].first = backingArray[index*2 +1].first;
		backingArray[index].second = backingArray[index*2 +1].second;
		backingArray[index*2 +1].first = tempPri;
		backingArray[index*2 +1].second = tempT;
	}//end if
}

template<class Pri, class T>
std::pair<Pri,T> Heap<Pri,T>::remove(){
	if(numItems==0)
		throw std::string("Please stop trying to remove from an empty heap.");

	std::pair<Pri,T> tmp;
	tmp.first = backingArray[0].first;
	tmp.second = backingArray[0].second;

	backingArray[0].first = backingArray[numItems-1].first;//swap bottom priority contents to the top
	backingArray[0].second = backingArray[numItems-1].second;

	trickleDown(0);
	numItems--;
	return tmp;
}

template<class Pri, class T>
unsigned long Heap<Pri,T>::getNumItems(){
	return numItems;
}
