#include <Windows.h>
#include <iostream>


	__declspec(naked) void Modifying(DWORD startingAdress, DWORD dwsize) {

	 
	__asm {
		
		push ebp
		mov	ebp, esp
		sub esp,4
		push eax
		push ecx
		
		
		mov ecx,startingAdress // Store the startAdress in the ECX register
		add ecx,dwsize // add the size of memory block to ecx register
		mov eax,startingAdress

		encryption:

		xor byte ptr ds:[eax], 0x17158742 // | EAX = H -> '1' , inc eax -> EAX= 2 -> 'E'
		
		inc eax
		cmp eax,ecx
		jl encryption // if eax < ecx , go to encryption

			pop eax
			pop ecx
			mov esp,ebp
			pop ebp
			ret
	}
}
int main() {

	char test[] = "Hello World";
	std::cout << test << " At Adress 0x" << &test << std::endl;

	printf("%s address-> 0x%X\n", test, &test);

	Modifying((DWORD)&test, strlen(test));
	printf("Modified %s address-> 0x%X\n", test, &test);

	std::cout << "Modified " << test << " At Adress 0x" << &test << std::endl;
	Modifying((DWORD)&test, strlen(test));

	printf("%s address-> 0x%X\n", test, &test);


	std::cout << "After decoded " << test << " At Adress 0x" << &test << std::endl;
	printf("%s address-> 0x%X\n", test, &test);

	getchar();
	return EXIT_SUCCESS;
}