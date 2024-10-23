#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 1024

char *gen_hash(char *sentence);
void gen_random_string(char *dest, int string_length);
char *random_permutations(char *str);
void swap(char *x, char *y);
int super_tetration(int g, int a, int z);
void clean_from_spaces(char *sentence);
//unsigned sqrt_cpu_int(unsigned long L);
void concat_numbers(int *arr, size_t size, char *result, size_t result_size);
int root(int input, int n);
int power(int g, int a);
void to_int_array(int count, int num);

int main() {
	int p = 23;
	int g = 5;
	char sentence[256];
	char clean_sentence[256];
	printf("Введите строку: ");
        scanf("%249[^\n]", &sentence);  
        
        
        char *cleaned_text = gen_hash(sentence);
        clean_from_spaces(cleaned_text);
        printf("%s\n", cleaned_text);
        int hash_size = strlen(cleaned_text);
        int int_hash;
        
        printf("%d", cleaned_text);
        
        int sum = 0;
        for (int i = 0; i < hash_size; i++) {
            int_hash = (int)cleaned_text[i];
        }
        
        int power = (int)int_hash;
        
        printf("%d ", (int)int_hash);
        
        
        printf("%d ", super_tetration(g, root(power, 5), p));
        int hashed = super_tetration(g, root(power, 5), p);
        
        
        int num = count_digits(hashed);     
        to_int_array(num, hashed);

        return 0;
}

// Function to free the allocated memory
void free_array(int* arr) {
    free(arr);
}

int count_digits(int n) {
    // For digit 0
    if(n == 0)
          return 1;
      
    int count = 0;

    // Remove last digit from number
    // till number is 0
    while (n != 0) {

        // Increment count
        count++;
        n /= 10;
    }

    // return the count of digit
    return count;
}

void to_int_array(int count, int num) {
    char *str_hashed;
    int digits[count];
    int i = count - 1;
    printf(" ");
    while (num > 0)
    {
        int digit = num % 10;
        num /= 10;
        digits[i] = digit;
        digits[i] += 97;
        printf("%c", digits[i]);  
        i--;
   }
   printf("\n"); 
}

int root(int input, int n)
{
    return round(pow(input, 1./n));
}

void concat_numbers(int *arr, size_t size, char *result, size_t result_size) {
    size_t pos = 0;
    for (size_t i = 0; i < size; i++) {
        int n = snprintf(result + pos, result_size - pos, "%d", arr[i]);
        if (n < 0) {
            fprintf(stderr, "Error formatting number %d", arr[i]);
            return;
        }
        pos += n;
    }
}

unsigned sqrt_cpu_int(unsigned long L) {
        unsigned div = 1, rslt = 0; 
	while (L > 0)
	{
	    L -= div,  div += 2; 
		rslt += L < 0 ? 0 : 1; 
	}
	return rslt; 
}

int power(int g, int a) {
       int production = 1;
       
       for (int i = 0; i < a; i++) {
              production *= g;
       }
       return production;
}

int super_tetration(int g, int a, int z) {
       a = power(g, a);
       int super_production = 1;
       
       for (int j = 0; j < a; j++) {
             super_production *= g;
       }
       return super_production;
}

void clean_from_spaces(char *sentence) {
      char res[512] = "";
      
      int j = 0;
      int i;
      for (i = 0; i < strlen(sentence) ; i++) {
          if (sentence[i] == ' ') 
          {
            if (j==0) continue;
            if (sentence[i+1] == ' ') continue;
          }
          res[j] = sentence[i];
          j++;
      }
      i = strlen(res);
      if(res[i-2] == ' ')
          res[i-2] = '\0';
          
      return res;
}

char *gen_hash(char *sentence) {
        char rand_str[512];     // Buffer for the random string

        // Remove spaces from the sentence
        char *src = sentence, *dst = sentence;
        while (*src != '\0') {
            if (*src != ' ') {
                *dst++ = *src;
            }
            src++;
        }
        *dst = '\0'; // Null-terminate the new string without spaces

        gen_random_string(rand_str, 24); // Generate a random string

        // Create a new string for the output
        char *output; // Static to return from the function safely
        output = strcat(sentence, rand_str);
        //snprintf(output, sizeof(output), "RandomString: %s, Original: %s", rand_str, sentence);
        
        return random_permutations(output);
}

void swap(char *x, char *y) {
        char temp;
        temp = *x;
        *x = *y;
        *y = temp;
}

char *random_permutations(char *str) {
        //char str[100];
        //printf("Enter a word: ");
        //scanf("%s", str); // Read input word

        int n = strlen(str);
        
        // Seed the random number generator
        srand(time(0));

        // Generate random permutations
        printf("Random permutations of the word:\n");
        for (int i = 0; i < 10; i++) { // Print 10 random permutations
            // Shuffle the string randomly using Fisher-Yates Algorithm
            for (int j = n - 1; j > 0; j--) {
                int k = rand() % (j + 1);
                swap(&str[j], &str[k]);
            }
            //printf("%s", str); // Print the shuffled string
        }

        return str;
}

void gen_random_string(char *dest, int string_length) {
        const char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; 
        int num_chars = sizeof(characters) - 1;
	
	
	//scanf("%249s", &string_length);
        for (int i = 0; i < string_length; ++i) {
                dest[i] = characters[rand() % num_chars]; // starting on '0', ending on '}'
        }
        dest[string_length] = '\0'; 
}
