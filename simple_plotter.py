
# simple function plotter in Python using pygame
# from Warren Sande - 4/2/2010
# Lee Bradley - user can enter function now - 4/6/2010

import pygame, sys
from math import *
import easygui
fs = easygui.enterbox("Enter your function",
    default = 'abs(x)**0.5 + 5 * x**3')
pygame.init()
width = 640
height = 480
screen = pygame.display.set_mode([width,height])
screen.fill([255, 255, 255])
xborder = 100
yborder = 60
numpoints = 1000

# define the initial min and max for x here:
xmin = -1
xmax = 1

def f(x):
    f = eval(fs)
    return f

def replot():
    global screen, xmin, xmax, ymin, ymax, x_scale, y_scale, numpoints

    plotPoints = []
    plotCoords = []
    ymin = 0
    ymax = 0
    delta = (xmax - xmin) / float(numpoints)

    # Calculate n points of the function over the defined range
    x = xmin
    for i in range (numpoints):
        y = f(x)
        plotPoints.append([x, y])
        x = x + delta

    # find min and max x and y for scaling
    for i in range (numpoints):
        if plotPoints[i][1] < ymin: ymin = plotPoints[i][1]
        if plotPoints[i][1] > ymax: ymax = plotPoints[i][1]

    # Calculate scale factors: values to x-y screen coords
    x_scale =  float(width-xborder) / (xmax - xmin)
    y_scale =  float(height-yborder) / (ymax - ymin)

    # Calculate plot coords for each point
    for i in range (numpoints):
        x = (plotPoints[i][0] - xmin) * x_scale + xborder / 2
        y = height - ((plotPoints[i][1] - ymin) * y_scale) - yborder / 2
        plotCoords.append([x, y])

    # draw axes
    x_axis = [[xmin, 0], [xmax, 0]]
    y_axis = [[0, ymin], [0, ymax]]
    xaxis_points = []
    yaxis_points = []
    for point in x_axis:
        x = (point[0] - xmin) * x_scale + xborder / 2
        y = height - ((point[1] - ymin) * y_scale) - yborder / 2
        xaxis_points.append([x, y])
    for point in y_axis:
        x = (point[0] - xmin) * x_scale + xborder / 2
        y = height - ((point[1] - ymin) * y_scale) - yborder / 2
        yaxis_points.append([x, y])

    # Draw scale marks
    xminrp = ('%.2e' % xmin).split('.')
    xmin_round = float(xminrp[0] + '.0e' + xminrp[1].split('e')[1])
    yminrp = ('%.2e' % ymin).split('.')
    ymin_round = float(yminrp[0] + '.0e' + yminrp[1].split('e')[1])

    xmaxrp = ('%.2e' % xmax).split('.')
    xmax_round = float(xmaxrp[0] + '.0e' + xmaxrp[1].split('e')[1])
    ymaxrp = ('%.2e' % ymax).split('.')
    ymax_round = float(ymaxrp[0] + '.0e' + ymaxrp[1].split('e')[1])

    xmintick_xloc = (xmin_round - xmin) * x_scale + xborder / 2
    ymintick_yloc = height - ((ymin_round - ymin) * y_scale) - yborder / 2
    xmintick = [[xmintick_xloc, xaxis_points[0][1] - 5], [xmintick_xloc, xaxis_points[0][1] + 5]]
    ymintick = [[yaxis_points[0][0] - 5, ymintick_yloc], [yaxis_points[0][0] + 5, ymintick_yloc]]

    xmaxtick_xloc = (xmax_round - xmin) * x_scale + xborder / 2
    ymaxtick_yloc = height - ((ymax_round - ymin) * y_scale) - yborder / 2
    xmaxtick = [[xmaxtick_xloc, xaxis_points[0][1] - 5], [xmaxtick_xloc, xaxis_points[0][1] + 5]]
    ymaxtick = [[yaxis_points[0][0] - 5, ymaxtick_yloc], [yaxis_points[0][0] + 5, ymaxtick_yloc]]

    xminlab_pos = [xmintick_xloc - 5, xaxis_points[0][1] + 5]
    yminlab_pos = [yaxis_points[0][0] - xborder/2, ymintick_yloc - 8]
    xmaxlab_pos = [xmaxtick_xloc - 5, xaxis_points[0][1] + 5]
    ymaxlab_pos = [yaxis_points[0][0] - xborder/2, ymaxtick_yloc - 8]

    screen.fill([255, 255, 255])
    xmin_font = pygame.font.Font(None, 20)
    xmin_surf = xmin_font.render(str(xmin_round), 1, (255, 0, 0))
    screen.blit(xmin_surf, xminlab_pos)
    ymin_font = pygame.font.Font(None, 20)
    ymin_surf = ymin_font.render(str(ymin_round), 1, (255, 0, 0))
    screen.blit(ymin_surf, yminlab_pos)

    xmax_font = pygame.font.Font(None, 20)
    xmax_surf = xmax_font.render(str(xmax_round), 1, (255, 0, 0))
    screen.blit(xmax_surf, xmaxlab_pos)
    ymax_font = pygame.font.Font(None, 20)
    ymax_surf = ymax_font.render(str(ymax_round), 1, (255, 0, 0))
    screen.blit(ymax_surf, ymaxlab_pos)

    pygame.draw.lines(screen, [0,0,0],False, plotCoords, 2)     # plot the function
    pygame.draw.lines(screen, [255,0,0],False, xaxis_points, 1) # plot the x-axis,
    pygame.draw.lines(screen, [255,0,0],False, yaxis_points, 1) # plot the y-axis,
    pygame.draw.lines(screen, [255,0,0],False, xmintick, 1)     # plot the xmin-tick,
    pygame.draw.lines(screen, [255,0,0],False, ymintick, 1)     # plot the ymin-tick,
    pygame.draw.lines(screen, [255,0,0],False, xmaxtick, 1)     # plot the xmax-tick,
    pygame.draw.lines(screen, [255,0,0],False, ymaxtick, 1)     # plot the ymax-tick,
    pygame.display.flip()

delay = 100
interval = 50
pygame.key.set_repeat(delay, interval)
pygame.display.set_caption(fs)
replot()
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                # zoom in
                xmax = xmax - (abs(xmax) * 0.1)
                xmin = xmin + (abs(xmin) * 0.1)
                replot()
            elif event.key == pygame.K_DOWN:
                # zoom out
                xmax = xmax + (abs(xmax) * 0.1)
                xmin = xmin - (abs(xmin) * 0.1)
                replot()
            elif event.key == pygame.K_LEFT:
                # pan left
                pan = abs(xmax - xmin) * 0.1
                xmax = xmax - pan
                xmin = xmin - pan
                replot()
            elif event.key == pygame.K_RIGHT:
                # pan right
                pan = abs(xmax - xmin) * 0.1
                xmax = xmax + pan
                xmin = xmin + pan
                replot()

