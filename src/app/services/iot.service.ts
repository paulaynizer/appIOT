import { Injectable } from '@angular/core';
import { Database, set, ref, update, onValue, remove } from '@angular/fire/database';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class FirebaseService {
  private dbPath = '/FirebaseIOT';

  constructor(private db: Database) { }
  /*
  public saveData(data: any): Promise<void> {
    const dbRef = ref(this.db, this.dbPath);
    return set(dbRef, data);
  }*/

  public updateData(data: any): Promise<void> {
    const dbRef = ref(this.db, this.dbPath);
    return update(dbRef, data);
  }

  public getData(): Observable<any> {
    const dbRef = ref(this.db, this.dbPath);
    return new Observable<any>(observer => {
      onValue(dbRef, snapshot => {
        observer.next(snapshot.val());
      });
    });
  }
  /*
  public deleteData(): Promise<void> {
    const dbRef = ref(this.db, this.dbPath);
    return remove(dbRef);
  }*/
}
