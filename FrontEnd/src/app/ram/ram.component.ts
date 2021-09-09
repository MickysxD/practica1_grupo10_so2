import { Component, OnInit } from '@angular/core';
import { ConngoService } from '../services/conngo.service';

import { HttpClient, HttpHeaders } from '@angular/common/http';
@Component({
  selector: 'app-ram',
  templateUrl: './ram.component.html',
  styleUrls: ['./ram.component.css']
})
export class RamComponent implements OnInit {
  
  url_sopes:any
  constructor(private http: HttpClient) { 
    this.url_sopes = "http://18.191.208.47:8080/";
    (async () => {
      while(true) { 
      // Do something before delay
        await this.delay(3000);
        this.obtener()
        // Do something after
      }
    })();

    
  }
  ngOnInit(): void {
   
  }
  delay(ms: number) {
    return new Promise(resolve => setTimeout(resolve, ms));
  }
  obtener(){
    let alb = this.http.post(this.url_sopes + 'ram', {})
    alb.subscribe(res => {
      if (res == null) {
        alert("Error")
      } else {
        console.log(JSON.parse(JSON.stringify(res)))
      }
    })
  }

}
