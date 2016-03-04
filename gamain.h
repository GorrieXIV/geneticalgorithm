/*

*/
class entities{
	public:
	float q, p1, p2; //the genes to be manipulated
	float angle, force; //product of each entities genes*interaction with the environment
	float fitness; //fitness score
	float x,y;
	
	entities(); //constructor

	private:
	
};

entities crossover(entities s1, entities s2, entities s3, entities s4, entities s5);

