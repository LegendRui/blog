## 函数柯里化

## 手写Promise
```
class MyPromise {
    // 构造函数，参数是一个函数
    /**
     * 
     * @param {*} executor: (resolve, reject) => {} 
     */
    constructor(executor) {
        // promise有3个状态，分别是pending、fulfilled和rejected
        this.state = 'pending';
        this.value = null;
        this.reason = null;
        this.callbacks = [];
        // 当调用resolve时，修改状态为fulfilled并将resolve的参数赋值给value
        const resolve = value => {
            if (this.state !== 'pending') return
            this.state = 'fulfilled'
            this.value = value
            // 改变完状态再调用then中注册的成功回调onFulfilled
            this.callbacks.forEach(callback => callback.fulfilled(value))
        }
        // 当调用reject时，修改状态为rejected并将
        const reject = reason => {
            if (this.state !== 'pending') return
            this.state = 'rejected'
            this.reason = reason
            this.callbacks.forEach(callback => callback.rejected(reason))
        }
        try {
            executor(resolve, reject)
        } catch (error) {
            reject(error)
        }
    }
    /**
     * 
     * @param {成功的回调} onFulfilled 
     * @param {失败的回调} onRejected 
     * @returns 返回一个Promise对象
     */
    then(onFulfilled, onRejected) {
        // onFulfillded可以不传，不传就生成一个默认的函数
        if (typeof onFulfilled !== 'function') onFulfilled = value => value
        if (typeof onRejected !== 'function') onRejected = reason => { throw reason }
        // then的方法返回一个Promise对象
        let promise = new MyPromise((resolve, reject) => {
            if (this.state === 'fulfilled') {
                // 如果事件已成功，执行成功的回调onFulfilled，由于A+规定then方法是微任务，此处用setTimeout宏任务模拟
                setTimeout(() => {
                    try {
                        this.resolvePromise(promise, onFulfilled(this.value), resolve, reject)
                    } catch (error) {
                        reject(error)
                    }
                });
            }
            // 如果事件已成功，执行成功的回调onFulfilled
            if (this.state === 'rejected') {
                setTimeout(() => {
                    try {
                        this.resolvePromise(promise, onRejected(this.reason), resolve, reject)
                    } catch (error) {
                        reject(error)
                    }
                })
            }
            // 如果事件还没有结果，则把回调放进回调列表里，等待完成后调用resolve，在resolve中执行
            if (this.state === 'pending') {
                this.callbacks.push({
                    fulfilled: () => {
                        setTimeout(() => {
                            try {
                                this.resolvePromise(promise, onFulfilled(this.value), resolve, reject)
                            } catch (error) {
                                reject(error)
                            }
                        })
                    },
                    rejected: () => {
                        setTimeout(() => {
                            try {
                                this.resolvePromise(promise, onRejected(this.reason), resolve, reject)
                            } catch (error) {
                                reject(error)
                            }
                        })
                    }
                })
            }
        })
        return promise
    }
    /**
     * 
     * @param {构造函数返回的对象} promise 
     * @param {执行回调事件返回的对象} result 
     * @param {构造函数用到的将状态设为成功的函数} resolve 
     * @param {构造函数用到的将状态设为成功的函数} reject 
     * @returns 
     */
    resolvePromise(promise, result, resolve, reject) {
        // 判断onFulfilled/onRejected返回的promise对象是不是自身，如果时自身会造成循环引用，得抛出异常避免这种情况
        if (promise === result) reject(new TypeError('Chaining cycle detected for promise'))
        if (result && typeof result === 'object' || typeof result === 'function') {
            // called帮助判断回调是否已经调用了
            let called
            try {
                let then = result.then
                if (typeof then === 'function') {
                    then.call(result, value => {
                        if (called) return
                        called = true
                        this.resolvePromise(promise, value, resolve, reject)
                    }, reason => {
                        if (called) return
                        called = true
                        reject(reason)
                    })
                } else {
                    if (called) return
                    called = true
                    resolve(result)
                }
            } catch (error) {
                if (called) return
                called = true
                reject(error)
            }
        } else {
            resolve(result)
        }
    }
}
```
