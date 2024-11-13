# Simple fractal program using Pygame to display results
# (Based on Kirby Urner's OO version)
# Warren Sande
# March, 2008

import pygame, sys

def mkpalette():
    global palette
    for i in range(0, 255):
        palette.append((i*5%200 + 20, i*7%200 + 20, i*11%200 + 20))
    return palette

def update_text():
    global f_surf, font_obj, coord_text
    ulxt = 'x = %.4e' % uleft_x
    ulyt = 'y = %.4e' % uleft_y
    lrxt = 'x = %.4e' % lright_x
    lryt = 'y = %.4e' % lright_y
    w = 'w = %.4e' % abs(uleft_x - lright_x)
    h = 'h = %.4e' % abs(uleft_y - lright_y)
    f_surf.blit(font_obj.render(ulxt, 0, (255, 255, 255)), (10, 10))
    f_surf.blit(font_obj.render(ulyt, 0, (255, 255, 255)), (10, 30))
    f_surf.blit(font_obj.render(lrxt, 0, (255, 255, 255)), (width - 100, height - 50))
    f_surf.blit(font_obj.render(lryt, 0, (255, 255, 255)), (width - 100, height - 30))
    f_surf.blit(font_obj.render(w, 0, (255, 255, 255)), (10, height - 50))
    f_surf.blit(font_obj.render(h, 0, (255, 255, 255)), (10, height - 30))

def check_keys():
    global f_surf, uleft_x, uleft_y, lright_x, lright_y, xwidth, ywidth
    changed_view = False
    for event in pygame.event.get():  
        if event.type == pygame.QUIT:
            pygame.quit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_DOWN:
                # pan down
                pan = abs(lright_y - uleft_y) * 0.2
                lright_y = lright_y - pan
                uleft_y = uleft_y - pan  
                changed_view = True      
            elif event.key == pygame.K_UP:
                # pan up
                pan = abs(lright_y - uleft_y) * 0.2
                lright_y = lright_y + pan
                uleft_y = uleft_y + pan
                changed_view = True 
            elif event.key == pygame.K_LEFT:
                # pan left
                pan = abs(lright_x - uleft_x) * 0.2
                lright_x = lright_x - pan
                uleft_x = uleft_x - pan
                changed_view = True 
            elif event.key == pygame.K_RIGHT:
                # pan right
                pan = abs(lright_x - uleft_x) * 0.2
                lright_x = lright_x + pan
                uleft_x = uleft_x + pan
                changed_view = True 
            elif event.key == pygame.K_PAGEUP:
                 # zoom in
                lright_x = lright_x - (abs(lright_x - uleft_x) * 0.1)
                uleft_x = uleft_x + (abs(uleft_x-lright_x) * 0.1)
                lright_y = lright_y + (abs(lright_y - uleft_y) * 0.1)
                uleft_y = uleft_y - (abs(uleft_y-lright_y) * 0.1)
                changed_view = True 
            elif event.key == pygame.K_PAGEDOWN:
                # zoom out
                lright_x = lright_x + (abs(lright_x - uleft_x) * 0.1)
                uleft_x = uleft_x - (abs(uleft_x - lright_x) * 0.1)
                lright_y = lright_y - (abs(lright_y - uleft_y) * 0.1)
                uleft_y = uleft_y + (abs(uleft_y - lright_y) * 0.1)
                changed_view = True 

    if changed_view:
        xwidth = lright_x - uleft_x
        ywidth = uleft_y  - lright_y
        f_surf.fill((0,0,0))
        update_text()
    return(changed_view)

def compute_fractal(n):
    global f_surf, xwidth, ywidth
    xwidth = lright_x - uleft_x
    ywidth = uleft_y  - lright_y 
    pixels = []
    xil = 0
    w = float(width)
    h = float(height)
    while xil < 4:                           # x interleave
        yil = 0
        while yil < 4:                       # y interleave
            for x in range (xil, width, 4):
                for y in range (yil, width, 4):
                    # get_coords
                    percentx = x/w
                    percenty = y/h
                    xp = uleft_x + percentx * xwidth
                    yp = uleft_y - percenty * ywidth
                    # fractal
                    z = complex(xp,yp)
                    o = complex(0,0)
                    dotcolor = 0
                    for trials in range(n):
                        if abs(o) <= 2.0:
                            o = o**2 + z
                        else:
                            dotcolor = trials
                            break
                    f_surf.set_at((x, y), palette[dotcolor])

                screen.blit(f_surf, [0,0,width,height])
                update_text()
                pygame.display.flip()
                if check_keys():
                    xil = -1
                    yil = -1
            yil +=1
        xil += 1

palette = [(0,0,0)]
width, height = 300, 300     # set window size
pygame.init()
mkpalette()
screen = pygame.display.set_mode((width, height))
f_surf = pygame.Surface((width, height))
font_obj = []
coord_text = []
font_obj = pygame.font.Font(None, 20)
uleft_x, uleft_y, lright_x, lright_y  = -2, 1.25, 0.5, -1.25
update_text()
xwidth, ywidth = 1, 1
compute_fractal(64)
clock = pygame.time.Clock()
done = False
while True:
    clock.tick(20)
    if check_keys():
        update_text()
        compute_fractal(64)

