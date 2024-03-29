/* Ticker library code is placed under the MIT license
 * Copyright (c) 2018 Stefan Staub
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Ticker1.h"

Ticker1::Ticker1(fptr callback, uint32_t timer, uint32_t repeat, resolution_t resolution) {
	this->resolution = resolution;
	if (resolution == MICROS) timer = timer * 1000;
	this->timer = timer;
	this->repeat = repeat;
	this->callback = callback;
	enabled = false;
	lastTime = 0;
	counts = 0;
	}

Ticker1::~Ticker1() {}

void Ticker1::start() {
	if (callback == NULL) return;
	if (resolution == MILLIS) lastTime = millis();
	else lastTime = micros();
	enabled = true;
	counts = 0;
	status = RUNNING;
	}

void Ticker1::resume() {
	if (callback == NULL) return;
	if (resolution == MILLIS) lastTime = millis() - diffTime;
	else lastTime = micros() - diffTime;
	if (status == STOPPED) counts = 0;
	enabled = true;
	status = RUNNING;
	}

void Ticker1::stop() {
	enabled = false;
	counts = 0;
	status = STOPPED;
	}

void Ticker1::pause() {
	if (resolution == MILLIS) diffTime = millis() - lastTime;
	else diffTime = micros() - lastTime;
	enabled = false;
	status = PAUSED;
	}

void Ticker1::update() {
	if (tick()) callback();
	}

bool Ticker1::tick() {
	if (!enabled)	return false;
	if (resolution == MILLIS) {
		if ((millis() - lastTime) >= timer) {
			lastTime = millis();
			if (repeat - counts == 1) enabled = false;
			counts++;				
	  	return true;
			}
		}
	else {
		if ((micros() - lastTime) >= timer) {
			lastTime = micros();
			if (repeat - counts == 1) enabled = false;
			counts++;
			return true;
			}
		}
	return false;
	}

void Ticker1::interval(uint32_t timer) {
	if (resolution == MICROS) timer = timer * 1000;
	this->timer = timer;
	}

uint32_t Ticker1::elapsed() {
	if (resolution == MILLIS) return millis() - lastTime;
	else return micros() - lastTime;
	}

status_t Ticker1::state() {
	return status;
	}

uint32_t Ticker1::counter() {
	return counts;
	}
