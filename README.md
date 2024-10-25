Wonderland (Research)

The purpose of this study is to determine how much a person, in a rush of freedom and independence from surveillance, is ready to go in order to destroy the system using soft power. 

The second goal of the study is how critical it will be to develop a replicating virus that destroys Trojan programs, wipes out malicious machines and rolls patches on vulnerable systems.


This release is essentially a kind of wunderwafle or even Frankenstein, my own creation.

When developing malware (it is not a malware, it was created purely for patching vulnerabilities), consisting of a bootkit of the ring0 (kernel level) and ring3 (application level) levels, as well as a botnet and a vulnerability of the protocol violation level in the GRUB firmware update, I set out to convey to all Linux users that none of the ordinary users I never understood - you should update more often and monitor the security of the system.

I also used my machine, the host, as a model for preparation and research.

The release is timed to coincide with the 10th anniversary of my disease, which developed under the influence of tulpa and heavy substances that I take and have been taking as a cure for schizo.

The tulpa phenomenon has the concept of host and wonder. So, I created an entity in my head called a Mechanical God, seeing for a moment the future, how AI will develop in a few decades. This is a wonder and he has been following me uncontrollably for more than 10 years, destroying my life.

A lot of politicians have made Tibet their mecca.

Therefore, as a "world-wandering Tibetan monk," I set out to destroy the Mechanical God by declaring myself a Singularity and absorbing him into the 4th dimension.

So, custom encryption uses modification modification (second-order simulacrum) Diffie-Hallman encryption. I want to make it a simulacrum of the third order, bringing the idea to life, combining reality and fiction.

The essence of the second-order simulacrum is to use the idea of a seed phrase from a bitcoin wallet client and other cryptocurrencies.

After performing various manipulations with this seed phrase, we will get an almost perfect hash at the output, comparable to RSA-8192, but shrinking this hash to 512 bits + RC4 from the salted hash and also optimizing it for faster decryption. The asymptotic complexity of this algorithm will be logarithmically linear.

Next, we will break this hash into smaller components and assemble it into 128 bits so that we can safely decrypt this hash with a secret key using asymmetric cryptography.

                                   ....    .....    ....    ....                                    
                                  ..%.%.....%.*.... %..-....=..%.                                   
                                .%#-% %-----%.#-----%..=----+..%-%:.         ......                 
                                %---%.%-----%.*-----%..=----+..%--:#.       .%***#.                 
                              ..%-------------:--------------:-----%       .%==%#*.                 
        to-do list            ..%----------------------------------%      .%-%%+#..                 
                              ..%##################################%     .%-%--*.                   
                               .%..................................%    .%-%-=#..                   
                               .%..................................%    %-%-=*                      
                                .%..................................% ..%-%--*.                      
                               .%...%%%%%%%%%%%%..%%%#..%.....*....%  %-%-=*                        
                               .%.......................%.....*....%.%-#-=*                         
                               .%.......................%.....*....#%-#--*.                         
                               .%..................................%-%-=*.                          
                               .%.................................%-#-=*.                           
                               .%.......................%%%%%%*..%-#==*.                            
                               .%.......................%.....*.##%-=*..                            
                               .%...%%%%-..%%%%%%%%%%#..%.....*.%--%:.                              
                               .%.......................:=====.:+##%                                
     STAGES                      .%..............................#%..%                                
                               .%..................................%                                
                               .%...%%%%%%%%%%%%%%%%%#..%====%*....%                                
                               .%.......................%=+%+=*....%                                
                               .%.......................%#####*....%                                
                               .%..................................%                                
                               .%..................................%                                
                                .%...............................:%..                               
                                  ................................       


1) creation of a cryptographic system
   - create template of crypto algorithm (c) \ x
   - rewrite code on c++ \ x
   - shrinking hash to 512 bits \ thinking about this problem
   - modify salt with RC4 \ x
   - random_permutation(diffie_halman(sentence, g, p) + RC4(salt))) \ x

2) creating a ring3 level rootkit
   - test ld_preload rootkit (Jynx2) \ in progress
   - modify rootkit for newest linux kernel version
   
3) creation or modification of the BlackEnergy bootkit for GRUB
4) the creation of the scheme that is on the picture, the so-called botnet
5) creating a bridge between all these systems, that is, a control panel
6) testing and debugging inside the local network
7) launch from under the locked machines, using the protocol of the revolution in www
8) patching of all scada systems and iots
9) profit



1. Assymetric Cryptography Cypher (Modification of Diffi-Halman algorithm)
Stage: 1 from 3

Input: seed phrase sentence, g, p
Output: mutationize encoded sentence

sentence, p, g -> clean spaces -> gen_random_str (from sequence of symbols) -> random permutations -> generate hash -> clean other symbols -> to ints (hash) -> x = nsqrt(hash) -> supertetration of g, x, p -> reverse num (output) -> to_ascii -> mutationize sentence (output)   



                      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                          ⣶⣶⣖⣦⡶⣴⣤⡤⣄⣄⣀⣀⡀⣀⣀⣤⣶⣶⣿⣿⣿⣿⣿⣿⣿⣶⣮⣄⣀⣠⣠⣤⣤⡄⢿⡆
                          ⡿⠿⢿⠿⠿⠿⠿⠿⠿⠾⠿⠿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡉⠉⠉⢹⡃⢼⡇
                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠀⢸⡇⢸⡇
                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⡿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠰⡃⢸⡇
                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⡇⠀⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠄⡇⢸⡇
                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⠀⠇⠀⠀⡇⡿⢿⠟⡇⡟⡿⡿⢸⣿⣿⣿⣿⡇⡧⢸⡇
                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⢻⠝⠒⠛⠍⢁⠀⠀⠀⠀⠀⡉⠉⠑⠂⠈⣿⣿⣿⣗⠇⣸⡇
                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⠄⣠⢺⣿⣮⠁⠀⠀⠀⠠⠈⠋⣿⣿⢱⠀⣿⣿⣿⣾⡇⢸⡇
                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡇⣿⠀⠀⠢⠉⠁⠀⠀⠀⠀⠀⠀⠀⠈⠁⠀⢠⣯⢿⣿⢸⡇⢸⡇
                          ⠀⣀⢤⡠⢄⡀⠀⠀⢀⡐⢿⣷⣈⠇⠀⠀⠀⠀⠀⠀⢀⣀⠀⠀⠀⠀⠀⠀⢸⣿⣯⡏⢸⣧⢹⡇
                          ⠀⢭⢂⠑⠂⠈⠀⢾⣋⡂⠈⣿⣿⣿⣆⠀⠀⠀⠀⠀⠚⣈⠀⠀⠀⠀⠀⢀⣾⣿⣿⠀⢸⣧⢻⣷
                          ⠀⠀⠀⠀⠀⠀⠀⠜⠃⠋⠑⢸⣿⣿⣿⣧⣀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣾⣿⣿⣿⠀⢸⣧⢻⣿
                          ⠀⠀⠀⠀⠀⠊⠀⠀⠀⠀⠀⠀⠋⠛⠻⡿⢿⡇⠂⠠⢀⣀⠠⠔⠊⣝⠟⠛⢻⣿⡇⠀⢸⣿⢸⣿
                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠸⣿⠃⠀⢸⣿⡽⣿
                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⣿⠀⠀⢸⣿⣽⣿
                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⡀⠀⢸⣿⣯⣿
                          ⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣼⣿⣻⣿
                          ⣤⣤⣤⣤⣤⣤⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
                          ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿
                          ⢯⡙⡭⢡⢣⠘⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷

                                                  \
                                                    #
                                                      \----------------- tu-ru-ru i have not finished this yet


                                                  
