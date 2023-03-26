import { Component, OnInit, OnDestroy } from '@angular/core';
import { Subscription } from 'rxjs';
import { FirebaseService } from 'src/app/services/iot.service';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage implements OnInit, OnDestroy {
  public humidity: number | undefined;
  public temperature: number | undefined;
  public led1: number | undefined;
  public led2: number | undefined;
  public led3: number | undefined;

  private firebaseSubscription!: Subscription;

  constructor(private firebaseService: FirebaseService) {}
  
  ngOnInit(){
    this.firebaseSubscription = this.firebaseService.getData()
    .subscribe((data: any) => {
      this.humidity = data.humidity;
      this.temperature = data.temperature;
      this.led1 = data.led.led1;
      this.led2 = data.led.led2;
      this.led3 = data.led.led3;
    });
  }

  ngOnDestroy() {
    this.firebaseSubscription.unsubscribe();
  }

  updateLedStatus() {
    const newData = {
      led: {
        led1: this.led1,
        led2: this.led2,
        led3: this.led3
      }
    };
    this.firebaseService.updateData(newData);
  }
  
  refreshData() {
    this.firebaseService.getData().subscribe((data: any) => {
      this.humidity = data.humidity;
      this.temperature = data.temperature;
      this.led1 = data.led.led1;
      this.led2 = data.led.led2;
      this.led3 = data.led.led3;
    });
  }
  
}
