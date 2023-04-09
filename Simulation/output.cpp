#include "output.hpp"

#include <iostream>


dec_info *Output::head;
dec_info *Output::end;
int Output::size_dec = 0;
int Output::mode = 2;

void Output::initialization()
{
    head = new dec_info;
    head->next = nullptr;
    head->prev = nullptr;
    head->info = "[initialization Output]\n";
    end = head;
    size_dec = 1;
}
//type: 0 - debag, 1 - log, 2 - output
void Output::cout(std::string input){

    if(mode == 0 || mode == 2){
        std::cout<<input;
    }
    if(mode == 1 || mode == 2){
        dec_info *block = new dec_info;
        block->next = nullptr;
        block->prev = end;
        block->info = input;
        end->next = block;
        end = block;
        size_dec++;
    }



}
std::string Output::get_and_delete_dec(){
    std::string buffer = "";
    if(mode == 1 || mode == 2){
        int i = 0;
        dec_info *i_ptr = head;

        while(i_ptr){

            if(i > 20){
                break;
            }

            if(i_ptr->next != nullptr){
                //if(i_ptr->next->next != nullptr){

                    //i++;
                    buffer += i_ptr->info;

                    //i_ptr->next->prev = nullptr;
                    //head = i_ptr->next;
                    //delete i_ptr;

                    i_ptr = i_ptr->next;
                //}
                //else{
                    //break;
                //}

            }
            else{
                break;
            }

        }
        free_dec(25);

    }
    return buffer;
}
/*
std::string Output::get_and_delete_dec(){
    std::string buffer = "";
    if(mode == 1 || mode == 2){
        int i = 0;
        dec_info *i_ptr = head;

        while(i_ptr){

            if(i > 10){
                break;
            }

            if(i_ptr->next != nullptr){
                if(i_ptr->next->next != nullptr){

                    //i++;
                    buffer += i_ptr->info;

                    //i_ptr->next->prev = nullptr;
                    //head = i_ptr->next;
                    //delete i_ptr;

                    i_ptr = i_ptr->next;
                }
                else{
                    break;
                }

            }
            else{
                break;
            }

        }
        free_dec(20);

    }
    return buffer;
}
*/

int Output::free_dec(int count){
    int i;
    dec_info *i_ptr = head;
    if(size_dec <= count){
        return 0;
    }
    while(i_ptr){

        if(size_dec <= count){
            break;
        }

        if(i_ptr->next != nullptr){
            if(i_ptr->next->next != nullptr){

                i++;
                size_dec--;

                i_ptr->next->prev = nullptr;
                head = i_ptr->next;
                delete i_ptr;

                i_ptr = i_ptr->next;
            }
            else{
                break;
            }

        }
        else{
            break;
        }

    }
    return i;
}

/*
std::string Output::get_and_delete_dec(){
    std::string buffer = "";
    int i = 0;
    dec_info *i_ptr = head;

    while(i_ptr){

        if(i > 10){
            break;
        }

        if(i_ptr->next != nullptr){
            if(i_ptr->next->next != nullptr){

                i++;
                buffer += i_ptr->info;
                i_ptr->next->prev = nullptr;
                head = i_ptr->next;
                delete i_ptr;

                i_ptr = i_ptr->next;
            }
            else{
                break;
            }

        }
        else{
            break;
        }

    }
    return buffer;
}
*/
std::string Output::get_buffer(){


}
