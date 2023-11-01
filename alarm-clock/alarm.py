
import datetime as d
import os
#Removes welcome message from pygame
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
from pygame import mixer



def alarm_or_timer():
    """Asks User if they would like to set an alarm or a timer
    
    Arguments:
        none
        
    Returns: 
        'Alarm' or 'Timer'. Depends on users input
    """
    dummy = True
    while(dummy):
        answer = input('Set "Alarm" or Set "Timer": ').strip()
        if(answer == 'Alarm'):
            dummy = False
            return answer
        elif(answer == 'Timer'):
            dummy = False
            return answer
        else:
            print("Not a given input. Try again. Press 'Q' to quit program")
            assert (answer != 'Q'), 'Quitting program'

def set_alarm():
    """Grabs time from user and sets off alarm when time is reached
    
    Arguments:
        none
        
    Returns: 
        none
    """
    
    print('What time would you like the alarm to be set for?')
    alarm_time = input("Please use 24H format of 'HH:MM:SS': ")

    #Validate if time exists
    while (validate(alarm_time) == 'FORMAT_ERROR'):
        print('What time would you like the alarm to be set for?')
        alarm_time = input("Please use 24H format of 'HH:MM:SS': ")
        
    current_time = str(d.datetime.now().strftime("%H:%M:%S"))
    
    print('Alarm set for: ', alarm_time)
    while(alarm_time != current_time):
        current_time = str(d.datetime.now().strftime("%H:%M:%S"))
    play_sound()
    
    return
    
def validate(a):
    """Veifies that the time the user inputted is obtainable.
    
    Arguments:
        a: the time the user inputted in a 24H format
        
    Returns: 
        'FORMAT_ERROR' if time the user inputted is unobtainable
    """
    split = a.split(':')
    if(len(a) > 8):
        print("Too many inputs. Please reinput.",'\n')
        return 'FORMAT_ERROR'
    
    for i in range(len(split)):
        if(i == 0):
            if(int(split[i]) >= 24):
                print('Hour can not be 24 and above. Please reinput.','\n')
                return 'FORMAT_ERROR'
            elif(int(split[i]) < 0):
                print('Hour can not be less than 0. Please reinput.','\n')
                return 'FORMAT_ERROR'
            else:
                pass
                
        elif(i == 1):
            if(int(split[i]) >= 60):
                print('Minute can not be 60 and above. Please reinput.','\n')
                return 'FORMAT_ERROR'
            elif(int(split[i]) < 0):
                print('Minute can not be less than 0. Please reinput.','\n')
                return 'FORMAT_ERROR'
            else:
                pass
        elif(i == 2):
            if(int(split[i]) >= 60):
                print('Second can not be 60 and above. Please reinput.','\n')
                return 'FORMAT_ERROR'
            elif(int(split[i]) < 0):
                print('Second can not be less than 0. Please reinput.','\n')
                return 'FORMAT_ERROR'
            else:
                pass
        else:
            return

def play_sound():
    """Seraches current directory for a '.mp3' file. If file is
    found it will play that file. Otherwise it will play
    the default '.mp3' file. Uses 'pygame' module to play '.mp3' file
    
    Arguments:
        none
        
    Returns: 
        none
    """
    mp3count = 0
    mixer.init()
    for file in os.listdir(os.getcwd()):

        if (file.endswith(".mp3")):
            mp3count = mp3count + 1
            if(file != 'maze.mp3'):
                mp3 = file     
    mixer.music.set_volume(0.9921875)
    
    if(mp3count == 1):
        mixer.music.load('maze.mp3')
        mixer.music.play()
        dummy = True
        while(dummy):
            t = input("'STOP' to stop alarm: ")
            if (t == 'STOP'):      
                mixer.music.stop()
                dummy = False
            else:
                pass 
    else:
        print("To add your own music add a '.mp3' into directory.")               
        mixer.music.load(mp3)
        mixer.music.play()
        dummy = True
        while(dummy):
            t = input("'STOP' to stop alarm: ")
            if (t == 'STOP'):      
                mixer.music.stop()
                dummy = False
            else:
                pass    
    return

def timer():
    """Grabs time from user and sets off timer.
    
    Arguments:
        none
        
    Returns: 
        none
    """
    print('How long would you like to set a timer for?')
    timer_time = input("Please use 24H format of 'HH:MM:SS': ")
    
    while (validate(timer_time) == 'FORMAT_ERROR'):
        print('What time would you like the alarm to be set for?')
        timer_time = input("Please use 24H format of 'HH:MM:SS': ")  
          
    current_time = str(d.datetime.now().strftime("%H:%M:%S"))
    #Add user inputted time to current time
    timer_time = timer_addition(timer_time, current_time)
    print('Timer set for: ', timer_time[0],':',timer_time[1],':',timer_time[2])
    while(timer_time != current_time):
        current_time = str(d.datetime.now().strftime("%H:%M:%S")).split(':')
    play_sound()
    
    return

def timer_addition(t,c):
    """Adds user inputted time to the current time. This new time will
    be used to determine when '.mp3' will go off
    
    Arguments:
        t: user inputted time
        c: current time
        
    Returns: 
        timer_split: the sum of the current time and the user inputted time
    """
    timer_split = t.split(':')
    current_split = c.split(':')
    
    #add time for seconds and minutes
    for i in range(len(timer_split),0,-1):
        timer_split [i-1] = str(int(timer_split[i-1]) + int(current_split[i-1]))
        if(int(timer_split[i-1]) > 60 ):
            timer_split[i-1] = str(int(timer_split[i-1]) - 60 )
            timer_split[i-2] = str(int(timer_split[i-2]) + 1)
            
            if(int(timer_split[i-1]) < 10):
                timer_split[i-1] = str(0) + str(timer_split[i-1])
                
    #Time is in 24 hour. turn to 00 instead of 24            
    if(int(timer_split[0]) > 23):
        timer_split[0] = str(int(timer_split[0]) - 24)
        
        if(int(timer_split[0]) < 10):
            timer_split[0] = str(0) + timer_split[0]
        
    return timer_split

def main():
    """Main function. Program can run from this function
    
    Arguments:
        none
        
    Returns: 
        none
    """
    choice = alarm_or_timer()
    if(choice == 'Alarm'):
        set_alarm()
        
    elif(choice == 'Timer'):
        timer()
    return
    
if __name__ == '__main__':
    main()