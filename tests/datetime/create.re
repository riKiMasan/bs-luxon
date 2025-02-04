open Jest;

open ExpectJs;

let getDateObject = (dt: DateTime.dt) => {
  "year": dt##year,
  "month": dt##month,
  "day": dt##day,
  "hour": dt##hour,
  "minute": dt##minute,
  "second": dt##second,
  "millisecond": dt##millisecond,
  "isValid": dt##isValid,
};

/*
 * .local()
 */
test("to work", () => {
  let now = DateTime.local();
  expect(Js.Date.getDate(now |> DateTime.toJSDate()))
  |> toBe(Js.Date.getDate(Js.Date.make()));
});

test("DateTime.local(2017) is the beginning of the year", () => {
  let dt = DateTime.local(~year=2017, ());
  expect(getDateObject(dt))
  |> toEqual({
       "year": 2017,
       "month": 1,
       "day": 1,
       "hour": 0,
       "minute": 0,
       "second": 0,
       "millisecond": 0,
       "isValid": true,
     });
});

test("DateTime.local(2017, 6) is the beginning of the month", () => {
  let dt = DateTime.local(~year=2017, ~month=6, ());
  expect(getDateObject(dt))
  |> toEqual({
       "year": 2017,
       "month": 6,
       "day": 1,
       "hour": 0,
       "minute": 0,
       "second": 0,
       "millisecond": 0,
       "isValid": true,
     });
});

test("DateTime.local(2017, 6, 12) is the beginning of 6/12", () => {
  let dt = DateTime.local(~year=2017, ~month=6, ~day=12, ());
  expect(getDateObject(dt))
  |> toEqual({
       "year": 2017,
       "month": 6,
       "day": 12,
       "hour": 0,
       "minute": 0,
       "second": 0,
       "millisecond": 0,
       "isValid": true,
     });
});

test("DateTime.local(2017, 6, 12, 5) is the beginning of the hour", () => {
  let dt = DateTime.local(~year=2017, ~month=6, ~day=12, ~hour=5, ());
  expect(getDateObject(dt))
  |> toEqual({
       "year": 2017,
       "month": 6,
       "day": 12,
       "hour": 5,
       "minute": 0,
       "second": 0,
       "millisecond": 0,
       "isValid": true,
     });
});

test("DateTime.local(2017, 6, 12, 5, 25) is the beginning of the minute", () => {
  let dt =
    DateTime.local(~year=2017, ~month=6, ~day=12, ~hour=5, ~minute=25, ());
  expect(getDateObject(dt))
  |> toEqual({
       "year": 2017,
       "month": 6,
       "day": 12,
       "hour": 5,
       "minute": 25,
       "second": 0,
       "millisecond": 0,
       "isValid": true,
     });
});

test(
  "DateTime.local(2017, 6, 12, 5, 25, 16) is the beginning of the second", () => {
  let dt =
    DateTime.local(
      ~year=2017,
      ~month=6,
      ~day=12,
      ~hour=5,
      ~minute=25,
      ~second=16,
      (),
    );
  expect(getDateObject(dt))
  |> toEqual({
       "year": 2017,
       "month": 6,
       "day": 12,
       "hour": 5,
       "minute": 25,
       "second": 16,
       "millisecond": 0,
       "isValid": true,
     });
});

test("DateTime#fromMillis creates DateTime object from epoch float", () => {
  let dt = DateTime.fromMillis(1497237916255.0) |> DateTime.setZone("UTC");
  expect(getDateObject(dt))
  |> toEqual({
       "year": 2017,
       "month": 6,
       "day": 12,
       "hour": 3,
       "minute": 25,
       "second": 16,
       "millisecond": 255,
       "isValid": true,
     });
});

test("DateTime#fromISO creates DateTime object from ISO", () => {
  let dt =
    DateTime.fromISO("2018-10-19T16:39:59Z") |> DateTime.setZone("UTC");
  expect(getDateObject(dt))
  |> toEqual({
       "year": 2018,
       "month": 10,
       "day": 19,
       "hour": 16,
       "minute": 39,
       "second": 59,
       "millisecond": 0,
       "isValid": true,
     });
});

test(
  "DateTime.valueOf(2017, 6, 12, 5, 25, 16, 255) returns correct epoch float",
  () => {
  let dt =
    DateTime.utc(
      ~year=2017,
      ~month=6,
      ~day=12,
      ~hour=3,
      ~minute=25,
      ~second=16,
      ~millisecond=255,
      (),
    )
    |> DateTime.valueOf();
  expect(dt) |> toEqual(1497237916255.0);
});

test(
  "DateTime.local(2017, 6, 12, 5, 25, 16, 255) is the beginning of the millisecond",
  () => {
    let dt =
      DateTime.local(
        ~year=2017,
        ~month=6,
        ~day=12,
        ~hour=5,
        ~minute=25,
        ~second=16,
        ~millisecond=255,
        (),
      );
    expect(getDateObject(dt))
    |> toEqual({
         "year": 2017,
         "month": 6,
         "day": 12,
         "hour": 5,
         "minute": 25,
         "second": 16,
         "millisecond": 255,
         "isValid": true,
       });
  },
);

test("DateTime.local(2019, 7, 32) is an invalid date", () => {
  let dt =
    DateTime.local(
      ~year=2019,
      ~month=7,
      ~day=32,
      ~hour=5,
      ~minute=25,
      ~second=16,
      ~millisecond=255,
      (),
    );

  let dateObj = getDateObject(dt);

  expect(dateObj##isValid) |> toEqual(false);
});

/*
 * .toFormat()
 */
test(
  "DateTime.(2017, 6, 12, 5, 25, 16, 255).toFormat('MM-dd-yyyy') returns correctly formatted string",
  () => {
    let dt =
      DateTime.local(
        ~year=2017,
        ~month=6,
        ~day=12,
        ~hour=4,
        ~minute=25,
        ~second=16,
        ~millisecond=255,
        (),
      )
      |> DateTime.toFormat("MM-dd-yyyy");
    expect(dt) |> toEqual("06-12-2017");
  },
);
