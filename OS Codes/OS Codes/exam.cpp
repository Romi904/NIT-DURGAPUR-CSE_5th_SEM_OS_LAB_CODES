
while(true)
{
	x=random();
	for(i=0;i<n;i++)
		cout<<"a";
	for(i=0;i<n;i++)
		V(S1);
	for(i=0;i<n;i++)
		V(S2);
}

while(true)
{
	P(S1);
	cout<<"b"
	V(S2);
}

process(i)
{
	mark[i]=false; 
	while(true){
		mark[i]=true;
		while(mark[1-i])
		{
			mark[i]=flase;
			while(flag[1-i]);
			mark[i]=true;
		}
		<Critical section code>
		mark[i]=false;
		remaining code....
}

process A 
{
	X1: P(a);
		cout<<"Hi"
		V(b);
		goto X1;
}

process B 
{
	X2: P(b);
		cout<<"Hello"
		V(b);
		goto X2;
}

process C 
{
	X3: P(b);
		cout<<"Bye"
		V(b);
		goto X3;
}

}	


