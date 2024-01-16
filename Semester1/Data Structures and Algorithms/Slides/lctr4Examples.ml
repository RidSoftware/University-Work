//**Age Example
	//**Iterative Format
	
	
	public int maxAgeLinear(){
		//**loop
		int oldest = -1;
		for (int = 0; i < size; i++){
			if(collection[i].getAge() > oldest){
				oldest =collection[i].getAge();
			}
		}
		return oldest;
	}
	//** note: iterative method
	
	
	//**Recursive Format
	
	
	public int maxAgeRecursive(int currentAge, int idx){
		//**Base Case
		if (idx == size){
			return currentAge;
		}
		
		//*Recursive Case
		else{
			//**IF AGE > CURRENT AGE, RETURN AGE THAT WAS JUST COMPARED TO PREVIOUS CURRENT AND UPDATED INDEX, ELSE RETURN JUST THE UPDATED INDEX
			if (collection[idx].getAge() > currentAge){
			return maxAgeRecursive(collection[idx].getAge(), idx++)
			{
			else{	
			return maxAgeRecursive(currentAge, idx++)
			}
		}
	}
