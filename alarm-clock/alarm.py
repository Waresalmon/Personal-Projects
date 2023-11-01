
import datetime as d
import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
from pygame import mixer



def alarm_or_timer():
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
            print("Not a given input. Try again. Press 'Q' to quit")
            assert (answer != 'Q'), 'Quitting program'

def set_alarm():
    print('What time would you like the alarm to be set for?')
    alarm_time = input("Please use 24H format of 'HH:MM:SS': ")
    #need to vefify that alarm_time is inputted correctly
    while (validate(alarm_time) == 'FORMAT_ERROR'):
        print('What time would you like the alarm to be set for?')
        alarm_time = input("Please use 24H format of 'HH:MM:SS': ")
    else:
        #grab time from computer
        print('Alarm set for: ', alarm_time)
        current_time = str(d.datetime.now().strftime("%H:%M:%S"))
        while(alarm_time != current_time):
            current_time = str(d.datetime.now().strftime("%H:%M:%S"))
        play_sound()
    
def validate(a):
    #Checks inputted format is obtainable in 24H time.
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
    
    #need to look for mp3 file in directoary
    #then play mp3
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

    print('How long would you like to set a timer for?')
    timer_time = input("Please use 24H format of 'HH:MM:SS': ")
    while (validate(timer_time) == 'FORMAT_ERROR'):
        print('What time would you like the alarm to be set for?')
        timer_time = input("Please use 24H format of 'HH:MM:SS': ")    
    current_time = str(d.datetime.now().strftime("%H:%M:%S"))
    timer_time = timer_addition(timer_time, current_time)
    print('Timer set for: ', timer_time[0],':',timer_time[1],':',timer_time[2])
    while(timer_time != current_time):
        current_time = str(d.datetime.now().strftime("%H:%M:%S")).split(':')
    play_sound()
    
    return

def timer_addition(t,c):
    timer_split = t.split(':')
    current_split = c.split(':')
    for i in range(len(timer_split),0,-1):
        timer_split [i-1] = str(int(timer_split[i-1]) + int(current_split[i-1]))
        if(int(timer_split[i-1]) > 60 ):
            timer_split[i-1] = str(int(timer_split[i-1]) - 60 )
            timer_split[i-2] = str(int(timer_split[i-2]) + 1)
            if(int(timer_split[i-1]) < 10):
                timer_split[i-1] = str(0) + str(timer_split[i-1])
    if(int(timer_split[0]) > 23):
        timer_split[0] = str(int(timer_split[0]) - 24)
        if(int(timer_split[0]) < 10):
            timer_split[0] = str(0 + timer_split[0])
        
    return timer_split

def main():
    choice = alarm_or_timer()
    if(choice == 'Alarm'):
        set_alarm()
    elif(choice == 'Timer'):
        timer()
    
if __name__ == '__main__':
    #making an alarm clock that plays a sound at a set time or in x minutes
    #can pass through function. But more readable this way
    #choice = alarm_or_timer()
    #can call in alarm_or_time function
    #if(choice == 'Alarm'):
    #    set_alarm()
    #elif(choice == 'Timer'):
    #timer()
    main()
    pass