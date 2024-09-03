#ifndef SNAKEOBSERVER_H
#define SNAKEOBSERVER_H

#pragma once

class SnakeObserver
{
    public:
        virtual void onNotifyEatFood() = 0;
};

#endif // SNAKEOBSERVER_H
